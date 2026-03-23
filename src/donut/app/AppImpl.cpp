#pragma peephole off

#include "app/AppImpl.hpp"
#include "mem/Memory.hpp"
#include "mem/OperatorNewDelete.hpp"

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
    , m_EB7C(0)
    , m_EB80(0)
    , mAlarm()
{
    OSInitSemaphore(&mSemaphore, 0);
    m_EBCC = false;

    for (s32 tick = OSGetTick() & (0xFFFF); tick != 0; tick--) {
        mRandom(1);
    }

    ptr_ = this;
    mem::OperatorNewDelete::SetDefaultAllocator(mem::Memory::Instance->sceneHeap());
}

AppImpl::~AppImpl() {
    DeleteInstance();
}
