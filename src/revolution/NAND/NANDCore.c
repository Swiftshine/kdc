#include "FS/fs.h"
#include "IPC/ipcclt.h"
#include "NAND/NANDErrorMessage.h"
#include "NAND/nand.h"
#include <revolution/ESP.h>
#include <revolution/NAND.h>
#include <revolution/OS.h>
#include <revolution/version.h>

#include <stdio.h>
#include <string.h>
#include <wchar.h>

#define NAND_BANNER_MAGIC 'WIBN'

typedef enum {
    NAND_LIB_UNINITIALIZED,
    NAND_LIB_INITIALIZING,
    NAND_LIB_INITIALIZED
} NANDLibState;

static void nandShutdownCallback(s32 result, void* arg);
static void nandGetTypeCallback(s32 result, void* arg);
static void nandLoggingCallback(BOOL arg1,  s32 result);
static BOOL nandOnShutdown(BOOL final, u32 event);
static void nandChangeDirCallback(s32 result, void* arg);

RVL_LIB_VERSION_KDC(NAND, "17:33:46");


static NANDLibState s_libState = NAND_LIB_UNINITIALIZED;
static char s_currentDir[64] ALIGN(32) = "/";
static OSShutdownFunctionInfo s_shutdownFuncInfo = {nandOnShutdown, 255};

static char s_homeDir[64] ALIGN(32);

void nandRemoveTailToken(char* newp, const char* oldp) {
    int i;

    if (oldp[0] == '/' && oldp[1] == '\0') {
        newp[0] = '/';
        newp[1] = '\0';
    } else {
        for (i = strlen(oldp) - 1; i >= 0; i--) {
            if (oldp[i] == '/') {
                if (i != 0) {
                    strncpy(newp, oldp, i);
                    newp[i] = '\0';
                    break;
                } else {
                    newp[0] = '/';
                    newp[1] = '\0';
                    break;
                }
            }
        }
    }
}

void nandGetHeadToken(char* head, char* rest, const char* path) {
    int i;

    for (i = 0; i <= strlen(path); i++) {
        if (path[i] == '/') {
            strncpy(head, path, i);
            head[i] = '\0';

            if (path[i + 1] == '\0') {
                *rest = '\0';
            } else {
                strcpy(rest, path + i + 1);
            }
            break;
        } else if (path[i] == '\0') {
            strncpy(head, path, i);
            head[i] = '\0';
            *rest = '\0';
            break;
        }
    }
}

void nandGetRelativeName(char* name, const char* path) {
    int i;

    if (strcmp("/", path) == 0) {
        strcpy(name, "");
    } else {
        for (i = strlen(path) - 1; i >= 0; i--) {
            if (path[i] == '/') {
                break;
            }
        }

        strcpy(name, path + i + 1);
    }
}

void nandConvertPath(char* abs, const char* dir, const char* rel) {
    char head[128];
    char rest[128];
    char notail[128];
    char newdir[128];

    if (strlen(rel) == 0) {
        strcpy(abs, dir);
        return;
    }

    nandGetHeadToken(head, rest, rel);

    if (strcmp(head, ".") == 0) {
        nandConvertPath(abs, dir, rest);
    } else if (strcmp(head, "..") == 0) {
        nandRemoveTailToken(notail, dir);
        nandConvertPath(abs, notail, rest);
    } else if (head[0] != '\0') {
        if (strcmp(dir, "/") == 0) {
            sprintf(newdir, "/%s", head);
        } else {
            sprintf(newdir, "%s/%s", dir, head);
        }
        nandConvertPath(abs, newdir, rest);
    } else {
        strcpy(abs, dir);
    }
}

BOOL nandIsRelativePath(const char* path) {
    return *path == '/' ? FALSE : TRUE;
}

BOOL nandIsPrivatePath(const char* path) {
    size_t len = sizeof("/shared2") - 1;
    if (strncmp(path, "/shared2", len) == NULL) {
        return TRUE;
    }
    return FALSE;
}


BOOL nandIsUnderPrivatePath(const char* path) {
    size_t len = sizeof("/shared2/") - 1;

    if (strncmp(path, "/shared2/", len) == 0 && path[len] != '\0') {
        return TRUE;
    }

    return FALSE;
}

BOOL nandIsInitialized(void) {
    return s_libState == NAND_LIB_INITIALIZED ? TRUE : FALSE;
}

void nandLoggingCallback(BOOL arg1,  s32 result) {
    if (result != ISFS_ERROR_UNKNOWN && result !=  IPC_RESULT_UNKNOWN) {
        return;
    }
    __NANDPrintErrorMessage(result);
}

//https://decomp.me/scratch/YC9xv
s32 nandConvertErrorCode(s32 result) {
    int i;

    // clang-format off
    const s32 errorMap[] = {        ISFS_ERROR_OK,                  NAND_RESULT_OK,
                            ISFS_ERROR_ACCESS,              NAND_RESULT_ACCESS,
                            ISFS_ERROR_CORRUPT,             NAND_RESULT_CORRUPT,
                            ISFS_ERROR_ECC_CRIT,            NAND_RESULT_ECC_CRIT,
                            ISFS_ERROR_EXISTS,              NAND_RESULT_EXISTS,
                            ISFS_ERROR_AUTHENTICATION,      NAND_RESULT_AUTHENTICATION,
                            ISFS_ERROR_INVALID,             NAND_RESULT_INVALID,
                            ISFS_ERROR_MAXBLOCKS,           NAND_RESULT_MAXBLOCKS,
                            ISFS_ERROR_MAXFD,               NAND_RESULT_MAXFD,
                            ISFS_ERROR_MAXFILES,            NAND_RESULT_MAXFILES,
                            ISFS_ERROR_MAXDEPTH,            NAND_RESULT_MAXDEPTH,
                            ISFS_ERROR_NOEXISTS,            NAND_RESULT_NOEXISTS,
                            ISFS_ERROR_NOTEMPTY,            NAND_RESULT_NOTEMPTY,
                            ISFS_ERROR_NOTREADY,            NAND_RESULT_UNKNOWN,
                            ISFS_ERROR_OPENFD,              NAND_RESULT_OPENFD,
                            ISFS_ERROR_UNKNOWN,             NAND_RESULT_UNKNOWN,
                            ISFS_ERROR_BUSY,                NAND_RESULT_BUSY,
                            ISFS_ERROR_SHUTDOWN,            NAND_RESULT_FATAL_ERROR,

                            IPC_RESULT_ACCESS,       NAND_RESULT_ACCESS,
                            IPC_RESULT_EXISTS,       NAND_RESULT_EXISTS,
                            IPC_RESULT_INTR,                               NAND_RESULT_UNKNOWN,
                            IPC_RESULT_INVALID,      NAND_RESULT_INVALID,
                            IPC_RESULT_CONN_MAX_INTERNAL,                               NAND_RESULT_UNKNOWN,
                            IPC_RESULT_NOEXISTS,     NAND_RESULT_NOEXISTS,
                            IPC_RESULT_EMPTYQUEUE,                               NAND_RESULT_UNKNOWN,
                            IPC_RESULT_BUSY,         NAND_RESULT_BUSY,
                            IPC_RESULT_UNKNOWN,                               NAND_RESULT_UNKNOWN,
                            IPC_RESULT_NOTREADY,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_ECC,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_ECC_CRIT,     NAND_RESULT_ECC_CRIT,
                            IPC_RESULT_BADBLOCK,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_INVALID_OBJTYPE,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_INVALID_RNG,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_INVALID_FLAG,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_INVALID_FORMAT,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_INVALID_VERSION,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_INVALID_SIGNATURE,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_VERIFY_FAILED,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_INTERNAL_FAILURE,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_ALLOC_FAILED,          NAND_RESULT_ALLOC_FAILED,
                            IPC_RESULT_INVALID_SIZE,                              NAND_RESULT_UNKNOWN
            };
    // clang-format on

    i = 0;

    if (result >= 0) {
        return result;
    }

    for (; i < ARRAY_SIZE(errorMap); i += 2) {
        if (result == errorMap[i]) {
                if (result == ISFS_ERROR_ECC_CRIT  || result == ISFS_ERROR_AUTHENTICATION || result == ISFS_ERROR_UNKNOWN ||
                result == IPC_RESULT_UNKNOWN || result == IPC_RESULT_ECC_CRIT) {
                char buf[128] ALIGN(64);
                sprintf(buf, "ISFS error code: %d", result);
                NANDLoggingAddMessageAsync(nandLoggingCallback, result, buf);
            }

            if (result < IPC_RESULT_INVALID_SIZE && result == ISFS_ERROR_UNKNOWN2 || result == ISFS_ERROR_MAXBLOCKS || result == ISFS_ERROR_MAXFILES || result == ISFS_ERROR_CORRUPT || result == ISFS_ERROR_BUSY || result == IPC_RESULT_BUSY || result == IPC_RESULT_ALLOC_FAILED) {
                __NANDPrintErrorMessage(result);
            }

            return errorMap[i + 1];
        }
    }

    OSReport("CAUTION!  Unexpected error code [%d] was found.\n", result);
    {
        char buf[128];
        sprintf(buf, "ISFS unexpected error code: %d", result);
        NANDLoggingAddMessageAsync(nandLoggingCallback, result, buf);
    }
    return NAND_RESULT_UNKNOWN;
}

void nandGenerateAbsPath(char* abs, const char* rel) {
    s32 len;

    if (strlen(rel) == 0) {
        strcpy(abs, "");
    } else if (nandIsRelativePath(rel)) {
        nandConvertPath(abs, s_currentDir, rel);
    } else {
        strcpy(abs, rel);
        len = strlen(abs);
        if (len != 0 && abs[len - 1] == '/' && len - 1 != 0) {
            abs[len - 1] = '\0';
        }
    }
}

void nandGetParentDirectory(char* dir, const char* path) {
    int i;

    for (i = strlen(path); i >= 0; i--) {
        if (path[i] == '/') {
            break;
        }
    }

    if (i == 0) {
        strcpy(dir, "/");
    } else {
        strncpy(dir, path, i);
        dir[i] = '\0';
    }
}

s32 NANDInit(void) {
    s32 result;
    ESTitleId tid;
    s32 fd;
    BOOL enabled;

    enabled = OSDisableInterrupts();

    if (s_libState == NAND_LIB_INITIALIZING) {
        OSRestoreInterrupts(enabled);
        return NAND_RESULT_BUSY;
    } else if (s_libState == NAND_LIB_INITIALIZED) {
        OSRestoreInterrupts(enabled);
        return NAND_RESULT_OK;
    }

    s_libState = NAND_LIB_INITIALIZING;
    OSRestoreInterrupts(enabled);

    result = ISFS_OpenLib();
    if (result == IPC_RESULT_OK) {

        result = ESP_InitLib();

        if (result == IPC_RESULT_OK) {
            result = ESP_GetTitleId(&tid);
        }

        if (result == IPC_RESULT_OK) {
            result = ESP_GetDataDir(tid, s_homeDir);
        }

        if (result == IPC_RESULT_OK) {
            strcpy(s_currentDir, s_homeDir);
        }

        ESP_CloseLib();

        if (result != IPC_RESULT_OK) {
            OSReport("Failed to set home directory.\n");
        }

        OSRegisterShutdownFunction(&s_shutdownFuncInfo);
        enabled = OSDisableInterrupts();
        s_libState = NAND_LIB_INITIALIZED;
        OSRestoreInterrupts(enabled);
        NANDSetAutoErrorMessaging(TRUE);
        OSRegisterVersion(__NANDVersion);
        return NAND_RESULT_OK;
    } else {
        enabled = OSDisableInterrupts();
        s_libState = NAND_LIB_UNINITIALIZED;
        OSRestoreInterrupts(enabled);
        nandConvertErrorCode(result);
    }
}

static BOOL nandOnShutdown(BOOL final, u32 event) {
    if (!final) {
        if (event == OS_SD_EVENT_SHUTDOWN) {
            volatile BOOL shutdown = FALSE;
            s64 start = OSGetTime();
            ISFS_ShutdownAsync(nandShutdownCallback, (void*)&shutdown);

            while (OS_TICKS_TO_MSEC(OSGetTime() - start) < 500) {
                if (shutdown) {
                    break;
                }
            }
        }

        return TRUE;
    }

    return TRUE;
}

static void nandShutdownCallback(s32 result, void* arg) {
#pragma unused(result)

    *(BOOL*)arg = TRUE;
}

static s32 nandChangeDir(const char* path, NANDCommandBlock* block, BOOL isAsync, BOOL hasPrivateAccess) {
    if (isAsync) {
        nandGenerateAbsPath(block->path, path);
        if (!hasPrivateAccess && nandIsPrivatePath(block->path)) {
            return ISFS_ERROR_ACCESS;
        } else {
            return ISFS_ReadDirAsync(block->path, NULL, &block->dirFileCount, nandChangeDirCallback, block);
        }
    } else {
        u32 num = 0;

        char absPath[NAND_MAX_PATH] = "";

        nandGenerateAbsPath(absPath, path);
        if (!hasPrivateAccess && nandIsPrivatePath(absPath)) {
            return ISFS_ERROR_ACCESS;
        } else {
            s32 err = ISFS_ReadDir(absPath, NULL, &num);
            if (err == ISFS_ERROR_OK) {
                BOOL enabled = OSDisableInterrupts();
                strcpy(s_currentDir, absPath);
                OSRestoreInterrupts(enabled);
            }
            return err;
        }
    }
}

s32 NANDChangeDir(const char* path) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    return nandConvertErrorCode(nandChangeDir(path, NULL, FALSE, FALSE));
}

static void nandChangeDirCallback(s32 result, void* arg) {
    NANDCommandBlock* block = (NANDCommandBlock*)arg;
    if (result == ISFS_ERROR_OK) {
        BOOL enabled = OSDisableInterrupts();
        strcpy(s_currentDir, block->path);
        OSRestoreInterrupts(enabled);
    }

    block->callback(nandConvertErrorCode(result), block);
}

s32 NANDGetHomeDir(char* out) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    strcpy(out, s_homeDir);
    return NAND_RESULT_OK;
}

void nandCallback(s32 result, void* arg) {
    NANDCommandBlock* block = (NANDCommandBlock*)arg;
    block->callback(nandConvertErrorCode(result), block);
}

static s32 nandGetType(const char* path, u8* type, NANDCommandBlock* block,
                       BOOL async, BOOL priv) {
    char absPath[64];
    u32 numFiles;
    s32 result;

    if (strlen(path) == 0) {
        return ISFS_ERROR_INVALID;
    }

    if (async) {
        nandGenerateAbsPath(block->path, path);

        if (!priv && nandIsUnderPrivatePath(block->path)) {
            return ISFS_ERROR_ACCESS;
        }

        block->type = type;
        return ISFS_ReadDirAsync(block->path, NULL, &block->dirFileCount,
                                 nandGetTypeCallback, block);
    } else {
        MEMCLR(&absPath);
        nandGenerateAbsPath(absPath, path);

        if (!priv && nandIsUnderPrivatePath(absPath)) {
            return ISFS_ERROR_ACCESS;
        }

        numFiles = 0;
        result = ISFS_ReadDir(absPath, NULL, &numFiles);
        if (result == IPC_RESULT_OK || result == ISFS_ERROR_ACCESS) {
            *type = NAND_FILE_TYPE_DIR;
            return IPC_RESULT_OK;
        } else if (result == ISFS_ERROR_INVALID) {
            *type = NAND_FILE_TYPE_FILE;
            return IPC_RESULT_OK;
        }

        return result;
    }
}

s32 NANDGetType(const char* path, u8* type) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    return nandConvertErrorCode(nandGetType(path, type, NULL, FALSE, FALSE));
}

s32 NANDPrivateGetTypeAsync(const char* path, u8* type,
                            NANDAsyncCallback callback,
                            NANDCommandBlock* block) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    block->callback = callback;
    return nandConvertErrorCode(nandGetType(path, type, block, TRUE, TRUE));
}

static void nandGetTypeCallback(s32 result, void* arg) {
    NANDCommandBlock* block = (NANDCommandBlock*)arg;

    if (result == IPC_RESULT_OK || result == ISFS_ERROR_ACCESS) {
        *block->type = NAND_FILE_TYPE_DIR;
        result = IPC_RESULT_OK;
    } else if (result == ISFS_ERROR_INVALID) {
        *block->type = NAND_FILE_TYPE_FILE;
        result = IPC_RESULT_OK;
    }

    block->callback(nandConvertErrorCode(result), block);
}

const char* nandGetHomeDir(void) {
    return s_homeDir;
}
