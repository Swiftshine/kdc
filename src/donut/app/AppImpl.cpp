#pragma peephole off

#include "app/AppImpl.hpp"
#include "mem/Memory.hpp"
#include "mem/OperatorNewDelete.hpp"
#include "snd/BGM.hpp"
#include "snd/SoundManager.hpp"
using namespace app;

AppImpl::AppImpl(System& rSystem)
    : mSystem(rSystem)
    , mReset()
    , mRomFontWrapper()
    , mGameScreen()
    , mDvdWatch(rSystem, mRomFontWrapper.font(), mGameScreen)
    , mFDGManager(mem::Memory::Instance->mem2FixHeap().allocFromTailAllocator())
    , mFileManager()
    , mResidentFile()
    , mFontManager()
    , mHIDManager()
    , mPerformanceController()
    , mPreLoadManager()
    , mRandom(hel::math::Random::Seed::Default())
    , mHomeButtonMenu(true)
    , mStorageManager()
    , mNandManager()
    , mMessageManager()
    , mAutoResetTimer()
    , mHIDErrorMenu()
    , mSaveInfo(mResidentFile)
    , mNANDErrorMenu(mResidentFile)
    , mEFBToLetterBox(mGameScreen)
    , mScene(nullptr)
    , m_EB80(0)
    , mAlarm()
{
    OSInitSemaphore(&mSemaphore, 0);
    mDrawDone = false;

    for (s32 tick = OSGetTick() & 0xFFFF; tick != 0; tick--) {
        mRandom(1);
    }

    ptr_ = this;
    mem::OperatorNewDelete::SetDefaultAllocator(mem::Memory::Instance->sceneHeap());
}

Reset::~Reset() { }

AppImpl::~AppImpl() {
    DeleteInstance();
}

void AppImpl::onBeforeSceneCreate() {
    mPerformanceController.resetSetting();
    mHIDManager.updateGame();
}

void AppImpl::onAfterSceneDestroy(bool arg1) {
    mHIDErrorMenu.onAfterSceneDestroy();
    mHIDManager.resetButtonConvertKind();
    mMessageManager.clear();
    mResidentFile.waitToFinish();
    mSaveInfo.afterSceneDestroy(arg1);
    mFileManager.clearFilesIfEnable();
    mPreLoadManager.waitToFinishLoading();
    mem::Memory::Instance->externalHeap().compaction();
}

void AppImpl::sceneLoop(scn::IScene& rScene) {
    onSceneStartProcess(rScene);

    do {
        mReset.process();
        beginFrameProcess();
        drawProcess(rScene);
        updateProcess(rScene);
        endFrameProcess(rScene);

        if (rScene.isSceneEnd()) {
            break;
        }
    } while (!mReset.isExecuted());

    onSceneEndProcess(rScene);
}

void AppImpl::onSceneStartProcess(scn::IScene& rScene) {
    mScene = &rScene;
    mResidentFile.startIfNecessary();
    mPerformanceController.onSceneStart();
    mDvdWatch.setBGMode(false);
}

void AppImpl::beginFrameProcess() {
    mDvdWatch.check();
    mPerformanceController.onFrameBegin();
    mHIDManager.updateMaster();
    mHIDManager.updateDebug();
    snd::SoundManager::Instance->update();
}

void AppImpl::updateProcess(scn::IScene& rScene) {
    if (!canFrameUpdate()) {
        return;
    }

    mHIDManager.updateGame();
    updateHBMProcess();

    if (!mHomeButtonMenu.isOpened() && !mReset.isExecuting() && !mNANDErrorMenu.isOpened()) {
        mHIDErrorMenu.update();
    }

    if (!mHomeButtonMenu.isOpened() && !mReset.isExecuting() && !mHIDErrorMenu.isOpened()) {
        mNANDErrorMenu.update();
        mSaveInfo.update();
    }

    if (canSceneUpdate()) {
        mAutoResetTimer.update();
    }

    if (canSceneUpdate()) {
        rScene.updateMain();
    }
}

#pragma push
#pragma optimize_for_size on
void AppImpl::updateHBMProcess() {
    if (mHomeButtonMenu.getIgnore()) {
        return;
    }

    bool found = false;

    for (u32 i = 0; i < MAX_HID_COUNT; i++) {
        if (mHIDManager.gameHID(i).button().isTrigger(0x8000)) {
            found = true;
            break;
        }
    }

    if (found) {
        if (!mHomeButtonMenu.isEnable()) {
            mHomeButtonMenu.startDisableIconAnimIfPossible();
        } else if (!mHomeButtonMenu.isOpened() && mHomeButtonMenu.isSetupFinished()) {
            mHomeButtonMenu.open();
        }
    }

    bool opened = mHomeButtonMenu.isOpened();
    mHomeButtonMenu.process(true);

    if (opened) {
        if (!mHomeButtonMenu.isOpened()) {
            snd::startAllSoundForBGMStopMenuClosed();
        }
    }
}
#pragma pop

void AppImpl::drawProcess(scn::IScene& rScene) {
    // not decompiled
}

void AppImpl::endFrameProcess(scn::IScene& rScene) {
    // not decompiled
}

void AppImpl::onSceneEndProcess(scn::IScene&) {
    mDvdWatch.setBGMode(true);
    mScene = nullptr;
}

bool AppImpl::canFrameUpdate() const {
    return mReset.canFrameUpdate();
}

bool AppImpl::canSceneUpdate() const {
    if (!canFrameUpdate()) {
        return false;
    }

    if (mHomeButtonMenu.isOpened()) {
        return false;
    }

    if (mHIDErrorMenu.isOpened()) {
        return false;
    }

    return !mNANDErrorMenu.isOpened();
}
