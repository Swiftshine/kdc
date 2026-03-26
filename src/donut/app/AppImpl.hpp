#ifndef DONUT_APP_APPIMPL_HPP
#define DONUT_APP_APPIMPL_HPP

#include <types.h>
#include <memory>
#include <revolution/OS.h>
#include <hel/common/NonCopyable.hpp>
#include <hel/common/ProtectedSingleton.hpp>
#include <hel/math/Random.hpp>

#include "app/AutoResetTimer.hpp"
#include "app/DvdWatch.hpp"
#include "app/HIDErrorMenu.hpp"
#include "app/NANDErrorMenu.hpp"
#include "app/PerformanceController.hpp"
#include "app/Reset.hpp"
#include "app/ResidentFile.hpp"
#include "app/RomFontWrapper.hpp"
#include "app/SaveInfo.hpp"
#include "app/System.hpp"
#include "file/FDGManager.hpp"
#include "file/FileManager.hpp"
#include "font/FontManager.hpp"
#include "gfx/EFBToLetterBox.hpp"
#include "gfx/IDrawer.hpp"
#include "gfx/GameScreen.hpp"
#include "hid/HIDManager.hpp"
#include "hbm/HomeButtonMenu.hpp"
#include "msg/Manager.hpp"
#include "nand/NandManager.hpp"
#include "preload/PreLoadManager.hpp"
#include "util/Alarm.hpp"
#include "scn/IScene.hpp"
#include "seq/ISequence.hpp"
#include "storage/StorageManager.hpp"

namespace app {

class AppImpl;

class AppImpl : public gfx::IDrawer, public hel::common::NonCopyable, public hel::common::ProtectedSingleton<AppImpl> {
public:
    AppImpl(System& rSystem);

    /* 0x8 */ virtual ~AppImpl();
    /* 0xC */ virtual void drawerExecDraw() override;

    void run(bool, bool, bool);
    void onDrawDone();
    void runWithRootSequence(std::auto_ptr<seq::ISequence> pSequence);
    void enterSceneSequence(seq::ISequence& rSequence);
    void onBeforeSceneCreate();
    void onAfterSceneDestroy(bool);
    void sceneLoop(scn::IScene&);
    void onSceneStartProcess(scn::IScene&);
    void beginFrameProcess();
    void updateProcess(scn::IScene&);
    void updateHBMProcess();
    void drawProcess(scn::IScene&);
    void endFrameProcess(scn::IScene&);
    void onSceneEndProcess(scn::IScene&);
    bool canFrameUpdate() const;
    bool canSceneUpdate() const;

    static void OnDrawDone();

    inline void DeleteInstance() {
        ptr_ = nullptr;
    }
private:
    /* 0x0008 */ System& mSystem;
    /* 0x000C */ Reset mReset;
    /* 0x0060 */ RomFontWrapper mRomFontWrapper;
    /* 0x0088 */ gfx::GameScreen mGameScreen;
    /* 0x008C */ DvdWatch mDvdWatch;
    /* 0x03D0 */ file::FDGManager mFDGManager;
    /* 0x0440 */ file::FileManager mFileManager;
    /* 0x0484 */ ResidentFile mResidentFile;
    /* 0x0854 */ font::FontManager mFontManager;
    /* 0x08E0 */ hid::HIDManager mHIDManager;
    /* 0x1E88 */ PerformanceController mPerformanceController;
    /* 0x1E9C */ preload::PreLoadManager mPreLoadManager;
    /* 0xDA00 */ hel::math::Random mRandom;
    /* 0xDA10 */ hbm::HomeButtonMenu mHomeButtonMenu;
    /* 0xDFF0 */ storage::StorageManager mStorageManager;
    /* 0xE018 */ nand::NandManager mNandManager;
    /* 0xE520 */ msg::Manager mMessageManager;
    /* 0xE6C8 */ AutoResetTimer mAutoResetTimer;
    /* 0xE6D4 */ HIDErrorMenu mHIDErrorMenu;
    /* 0xE744 */ SaveInfo mSaveInfo;
    /* 0xEAFC */ NANDErrorMenu mNANDErrorMenu;
    /* 0xEB64 */ gfx::EFBToLetterBox mEFBToLetterBox;
    /* 0xEB7C */ scn::IScene* mScene;
    /* 0xEB80 */ s32 m_EB80; // maybe a pointer?
    /* 0xEB84 */ s32 m_EB84;
    /* 0xEB8C */ util::Alarm mAlarm;
    /* 0xEB90 */ STRUCT_FILL(0x30);
    /* 0xEBC0 */ OSSemaphore mSemaphore;
    /* 0xEBCC */ bool mDrawDone;
};


}

#endif
