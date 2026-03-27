#ifndef DONUT_UTIL_FRAME_COUNTER_HPP
#define DONUT_UTIL_FRAME_COUNTER_HPP

#include <types.h>

namespace util {
    class FrameCounter {
    public:
        //Note: Gets merged into OSCreateAlarm
        FrameCounter();
        //Note: Gets merged into ocoll::Gimmick::Gimmick(ocoll::Manager&)
        FrameCounter(u32 endFrame);

        //Note: Gets merged into nw4r::snd::detail::BasicSound::DetachPlayerHeap(nw4r::snd::detail::PlayerHeap*)
        void reset();
        //Note: Gets merged into lyt::TagUtil::Iterator$48809TagUtil_cpp::onNormalChar(wchar_t)
        void advance();
        //Note: Gets merged into nw4r::snd::detail::AxManager::GetZeroBufferAddress()
        u32 frame() const;
        //Note: Gets merged into GKI_getfirst
        u32 maxFrame() const;
        void reset(u32 endFrame);
        bool isEnd() const;
        void advanceIfNotEnd();
        void setEnd();
        void setEndIfNotEnd();
        f32 normalizedFrame() const;
        f32 inversedNormalizedFrame() const;

        /* 0x0 */ u32 mEndFrame;
        /* 0x4 */ u32 mCurrentFrame;
    };
}

#endif
