#ifndef RVL_SDK_ARC_H
#define RVL_SDK_ARC_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct ARCHandle {
    void* archiveStartAddr; // at 0x0
    void* FSTStart;         // at 0x4
    void* fileStart;        // at 0x8
    u32 entryNum;           // at 0xC
    char* FSTStringStart;   // at 0x10
    u32 FSTLength;          // at 0x14
    s32 currDir;            // at 0x18
} ARCHandle;

typedef struct ARCFileInfo {
    ARCHandle* handle; // at 0x0
    u32 startOffset;   // at 0x4
    u32 length;        // at 0x8
} ARCFileInfo;

typedef struct ARCDir {
    ARCHandle* handle; // at 0x0
    u32 entryNum;      // at 0x4
    u32 location;      // at 0x8
    u32 next;          // at 0xC
} ARCDir;

typedef struct ARCDirEntry {
    ARCHandle* handle; // at 0x0
    u32 entryNum;      // at 0x4
    BOOL isDir;        // at 0x8
    char* name;        // at 0xC
} ARCDirEntry;

//gets inlined in arc.c but besides that unused
BOOL ARCGetCurrentDir(ARCHandle* handle, char* string, u32 maxlen);
BOOL ARCInitHandle(void* bin, ARCHandle* handle);
BOOL ARCOpen(ARCHandle* handle, const char* path, ARCFileInfo* info);
BOOL ARCFastOpen(ARCHandle* handle, s32 entrynum, ARCFileInfo* info);
s32 ARCConvertPathToEntrynum(ARCHandle* handle, const char* path);
void* ARCGetStartAddrInMem(ARCFileInfo* info);
//unused
u32 ARCGetStartOffset(ARCFileInfo* info);
u32 ARCGetLength(ARCFileInfo* info);
//Note: Merged into nw4r::ut::DvdFileStream::CanCancel() const
BOOL ARCClose(ARCFileInfo* info);

BOOL ARCChangeDir(ARCHandle* handle, const char* path);
BOOL ARCOpenDir(ARCHandle* handle, const char* path, ARCDir* dir);

BOOL ARCReadDir(ARCDir* dir, ARCDirEntry* entry);
//Note: Merged into nw4r::ut::DvdFileStream::CanCancel() const
BOOL ARCCloseDir(ARCDir* dir);
#ifdef __cplusplus
}
#endif
#endif
