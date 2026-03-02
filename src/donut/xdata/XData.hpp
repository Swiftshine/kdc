#ifndef DONUT_XDATA_HPP
#define DONUT_XDATA_HPP

#include <types.h>
namespace xdata {

struct XDataHeader {
    /* 0x0 */ s32 mMagic;
    /* 0x4 */ u16 mBOM;
    /* 0x6 */ u8 mVersion[2];
    /* 0x8 */ u32 mFilesize;
    /* 0xC */ u32 unk;
};

namespace XData {
    inline static void* dataHeadAddress(XDataHeader* pHeader) {
        bool magic = false, bom = false, size = false;

        if (pHeader != nullptr && pHeader->mMagic == 'XBIN') {
            magic = true;
        }

        if (magic && pHeader->mBOM == 0x1234) {
            bom = true;
        }

        if (bom && pHeader->mFilesize >= sizeof(XDataHeader)) {
            size = true;
        }

        if (size) {
            return reinterpret_cast<char*>(pHeader) + sizeof(XDataHeader);
        }

        return nullptr;
    }
};
}

#endif
