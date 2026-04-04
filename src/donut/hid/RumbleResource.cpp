#pragma peephole off
#include <donut/hid/RumbleResource.hpp>
#include <donut/xdata/XData.hpp>

namespace hid {
    namespace {
        const char* T_DAT_PATH_TABLE[2] = {
            "hid/rumble/Rumble.dat.cmp",
            "hid/rumble/subgame/Rumble.dat.cmp"
        };
    }

    RumbleResource::RumbleResource(hid::RumbleResourceKind kind)
        : mFileAccessor(T_DAT_PATH_TABLE[kind], false)
        , mRumbleData((xdata::XData*)mFileAccessor.block().mStartAddress)
    { }

    //https://decomp.me/scratch/2oK6D
    u32 RumbleResource::commandList(u32 arg1) const {
        u32 val;
        if (mRumbleData->isValidData()) {
            val = mRumbleData->header()->mMagic + 16;
        } else {
            val = 0;
        }

        u32 val2 = val  + arg1 * 4;

        u32 magic = mRumbleData->header()->mMagic;

        if (!mRumbleData->isValidData()) {
            return 0;
        }

        if (val2 < 16 || mRumbleData->header()->mFilesize  < val2) {
            return 0;
        }
        return mRumbleData->header()->mMagic + val2;
    }
}
