#ifndef DONUT_GFX_GXFIFOMEMORYMANAGER_HPP
#define DONUT_GFX_GXFIFOMEMORYMANAGER_HPP

#include <hel/common/PrivateSingleton.hpp>
#include <donut/util/Mutex.hpp>

namespace gfx {

    class GXFifoMemoryManager : public hel::common::PrivateSingleton<GXFifoMemoryManager> {
    public:
        GXFifoMemoryManager(u32 size, u32 arg2);
        ~GXFifoMemoryManager();

        void* data();
        void setWriteEnable();
        //Note: Merged into scn::step::gimmick::SuperStop::onSuperStopStarted(const scn::step::spstop::Manager&)
        void setWriteDisable();
        //NOTE: Merged into GKI_getfirst
        u32 size() const;
        //NOTE: merged into pause::PageCommand::pageMainLayout()
        util::Mutex* mutex();

        private:
        /* 0x00 */ u32 mSize;
        /* 0x04 */ u32 m_4;
        /* 0x08 */ void* mData;
        /* 0x0C */ bool mWriteEnabled;
        /* 0x10 */ util::Mutex mMutex;
    };

}

#endif
