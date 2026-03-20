#ifndef DONUT_APP_APPIMPL_HPP
#define DONUT_APP_APPIMPL_HPP

#include <types.h>
#include <revolution/OS.h>

namespace app {

class AppImpl {
public:
    AppImpl();

    /* 0x8 */ ~AppImpl();
    /* 0xC */ virtual void drawerExecDraw();

private:
    /* 0x0004 */ void* m_4;
    /* 0x0008 */ void* mSystem; // app::System
    /* 0x000C */ STRUCT_MEMBER(mReset, 0x54); // app::Reset
    /* 0x0060 */ STRUCT_MEMBER(mRomFontWrapper, 0x28); // app::RomFontWrapper
    /* 0x0088 */ STRUCT_MEMBER(mGameScreen, 4); // gfx::GameScreen
    /* 0x008C */ STRUCT_MEMBER(mDvdWatch, 0x344); // app::DvdWatch
    /* 0x03D0 */ STRUCT_MEMBER(mFDGManager, 0x70); // file::FDGManager
    /* 0x0440 */ STRUCT_MEMBER(mFileManager, 0x44); // file::FileManager
    /* 0x0484 */ STRUCT_MEMBER(mResidentFile, 0x3D0); // app::ResidentFile
    /* 0x0854 */ STRUCT_MEMBER(mFontManager, 0x8C); // font::FontManager
    /* 0x08E0 */ STRUCT_MEMBER(mHIDManager, 0x15A8); // hid::HIDManager
    /* 0x1E88 */ STRUCT_MEMBER(mPerformanceController, 0x14); // app::PerformanceController
    /* 0x1E9C */ STRUCT_MEMBER(mPreLoadManager, 0xBB64); // preload::PreLoadManager
    /* 0xDA00 */ STRUCT_MEMBER(mRandom, 0x10); // hel::math::Random
    /* 0xDA10 */ STRUCT_MEMBER(mHomeButtonMenu, 0x5E0); // hbm::HomeButtonMenu
    /* 0xDFF0 */ STRUCT_MEMBER(mStorageManager, 0x28); // storage::StorageManager
    /* 0xE018 */ STRUCT_MEMBER(mNandManager, 0x508); // nand::NandManager
    /* 0xE520 */ STRUCT_MEMBER(mMessageManager, 0x1A8); // msg::Manager
    /* 0xE6C8 */ STRUCT_MEMBER(mAutoResetTimer, 0xC); // app::AutoResetTimer
    /* 0xE6D4 */ STRUCT_MEMBER(mHIDErrorMenu, 0x70); // app::HIDErrorMenu
    /* 0xE744 */ STRUCT_MEMBER(mSaveInfo, 0x3B8); // app::SaveInfo
    /* 0xEAFC */ STRUCT_MEMBER(mNANDErrorMenu, 0x68); // app::NANDErrorMenu
    /* 0xEB64 */ STRUCT_MEMBER(mEFBToLetterBox, 0x18); // gfx::EFBToLetterBox
    /* 0xEB7C */ s32 m_EB7C;
    /* 0xEB80 */ s32 m_EB80;
    /* 0xEB84 */ s32 m_EB84;
    /* 0xEB8C */ STRUCT_MEMBER(mAlarm, 0x8); // util::Alarm
    /* 0xEB90 */ STRUCT_FILL(0x30);
    /* 0xEBC0 */ OSSemaphore mSemaphore;
    /* 0xEBCC */ bool m_EBCC;
};


}

#endif
