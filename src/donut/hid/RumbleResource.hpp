#ifndef DONUT_HID_RUMBLE_RESOURCE_HPP
#define DONUT_HID_RUMBLE_RESOURCE_HPP

#include <donut/file/FileAccessor.hpp>

namespace xdata {
    class XData;
};

namespace hid {

    enum RumbleResourceKind {
        RUMBLE_RESOURCE_MAIN,
        RUMBLE_RESOURCE_SUBGAME,
    };

    class RumbleResource {
    public:
        RumbleResource(RumbleResourceKind kind);
        u32 commandList(u32) const;

        /* 0x0 */ file::FileAccessor mFileAccessor;
        /* 0x4 */ xdata::XData* mRumbleData;
    };
}
#endif
