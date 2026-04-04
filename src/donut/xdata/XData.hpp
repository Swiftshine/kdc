#ifndef DONUT_XDATA_HPP
#define DONUT_XDATA_HPP

#include <types.h>
namespace xdata {

class XData {
private:
    struct XDataHeader {
        /* 0x0 */ s32 mMagic;
        /* 0x4 */ u16 mBOM;
        /* 0x6 */ u8 mVersion[2];
        /* 0x8 */ u32 mFilesize;
        /* 0xC */ u32 unk;
    };
public:
    #if defined(DONUT_INLINE)
    inline void* dataHeadAddress() {
        XDataHeader* header = &mHeader;

        bool magic = false, bom = false, size = false;

        if (header != nullptr && header->mMagic == 'XBIN') {
            magic = true;
        }

        if (magic && header->mBOM == 0x1234) {
            bom = true;
        }

        if (bom && header->mFilesize >= sizeof(XData)) {
            size = true;
        }

        if (size) {
            return reinterpret_cast<char*>(header) + sizeof(XData);
        }

        return nullptr;
    }

    #else
    void* dataHeadAddress();
    #endif

    bool isValidData() const;

    inline XDataHeader* header() const {
        return (XDataHeader*)&mHeader;
    }

private:
    /* 0x0 */ XDataHeader mHeader;
};



    // bool XData::isValidData() {
    //     return header != nullptr && header->magic == 0x5842494e && header->bom == 0x1234 && header->filesize > sizeof(XDataHeader) - 1;
    // }

    // void* XData::labelAddressWithReference(u32 address) {
    //     if (isValidData() && address >= sizeof(XDataHeader) && address < header->filesize) {
    //         return header + (address - 6);
    //     }

    //     return nullptr;
    // }

};

#endif
