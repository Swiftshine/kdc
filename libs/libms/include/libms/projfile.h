#ifndef LIBMS_PROJFILE_H
#define LIBMS_PROJFILE_H

#include <libms/commonbin.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ProjectInfo {
    /* 0x00 */ struct MsbInfo mBase;
    /* 0x10 */ int mCLR1;
    /* 0x14 */ int mCLB1;
    /* 0x18 */ int mALB1;
    /* 0x1C */ int mATI2;
    /* 0x20 */ int mALI2;
    /* 0x24 */ int mTGG2;
    /* 0x28 */ int mTAG2;
    /* 0x2C */ int mTGP2;
    /* 0x30 */ int mTGL2;
    /* 0x34 */ int mSYL3;
    /* 0x38 */ int mSLB1;
    /* 0x3C */ int mCTTI;
};

struct ProjectInfo *LMS_InitProject(void *data);
//NOTE: Merged into LMS_CloseMessage
void LMS_CloseProject(struct ProjectInfo *info);
const wchar_t* LMS_GetTagName(struct ProjectInfo* info, unsigned short arg2, unsigned short arg3);
const wchar_t* LMS_GetTagGroupName(struct ProjectInfo* info, unsigned short arg2);
const wchar_t* LMS_GetTagListItemName(struct ProjectInfo* info, unsigned short arg2, unsigned short arg3,
    unsigned short arg4, unsigned short arg5);

#ifdef __cplusplus
}
#endif

#endif
