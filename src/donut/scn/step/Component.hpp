#ifndef DONUT_SCN_STEP_COMPONENT_HPP
#define DONUT_SCN_STEP_COMPONENT_HPP

#include "mem/ExplicitScopedPtr.hpp"

#include "scn/step/Context.hpp"
#include "scn/step/core/SphereAccessor.hpp"
#include "scn/step/map/DataFile.hpp"

using mem::ExplicitScopedPtr;

namespace scn { namespace step {

class Component {
private:
    typedef int placeholder_t;
public:

private:
    /* 0x00 */ ExplicitScopedPtr<Context> mContext;
    /* 0x04 */ ExplicitScopedPtr<map::DataFile> mDataFile;
    /* 0x08 */ ExplicitScopedPtr<core::SphereAccessor> mSphereAccessor;
    /* 0x0C */ ExplicitScopedPtr<placeholder_t> mSceneChanger;
    /* 0x10 */ ExplicitScopedPtr<placeholder_t> mResFileRepository;
    /* 0x14 */ ExplicitScopedPtr<placeholder_t> mG3DRootSet;
    /* 0x18 */ ExplicitScopedPtr<placeholder_t> mEffectManager;
    /* 0x1C */ ExplicitScopedPtr<placeholder_t> mAreaLightManager;
    /* 0x20 */ ExplicitScopedPtr<placeholder_t> mMintManager;
    /* 0x24 */ ExplicitScopedPtr<placeholder_t> mRumbleManager;
    /* 0x28 */ ExplicitScopedPtr<placeholder_t> mPermSoundSE;
    /* 0x2C */ ExplicitScopedPtr<placeholder_t> mAreaOperation;
    /* 0x30 */ ExplicitScopedPtr<placeholder_t> mBGMController;
    /* 0x34 */ ExplicitScopedPtr<placeholder_t> mPauseTrigger;
    /* 0x38 */ ExplicitScopedPtr<placeholder_t> mOstopManager;
    /* 0x3C */ ExplicitScopedPtr<placeholder_t> mSuperStopManager;
    /* 0x40 */ ExplicitScopedPtr<placeholder_t> mPermEffect;
    /* 0x44 */ ExplicitScopedPtr<placeholder_t> mPreLoadReq;
    /* 0x48 */ ExplicitScopedPtr<placeholder_t> mBgFadeWithoutLand;
    /* 0x4C */ ExplicitScopedPtr<placeholder_t> mBgFade;
    /* 0x50 */ ExplicitScopedPtr<placeholder_t> mBgFadeOverGimmick;
    /* 0x54 */ ExplicitScopedPtr<placeholder_t> mFgFade;
    /* 0x58 */ ExplicitScopedPtr<placeholder_t> mScreenFade;
    /* 0x5C */ ExplicitScopedPtr<placeholder_t> mWip;
    /* 0x60 */ ExplicitScopedPtr<placeholder_t> mCinemaScope;
    /* 0x64 */ ExplicitScopedPtr<placeholder_t> mAbilityGetFade;
    /* 0x68 */ ExplicitScopedPtr<placeholder_t> mSuperFade;
    /* 0x6C */ ExplicitScopedPtr<placeholder_t> mSuperBackPicture;
    /* 0x70 */ ExplicitScopedPtr<placeholder_t> mSfxManager;
    /* 0x74 */ ExplicitScopedPtr<placeholder_t> mShadowRoot;
    /* 0x78 */ ExplicitScopedPtr<placeholder_t> mDarknessRoot;
    /* 0x7C */ ExplicitScopedPtr<placeholder_t> mDarknessAdjust;
    /* 0x80 */ ExplicitScopedPtr<placeholder_t> mInfoManager;
    /* 0x84 */ ExplicitScopedPtr<placeholder_t> mPauseManager;
    /* 0x88 */ ExplicitScopedPtr<placeholder_t> mCameraController;
    /* 0x8C */ ExplicitScopedPtr<placeholder_t> mBgCamera;
    /* 0x90 */ ExplicitScopedPtr<placeholder_t> mCameraAccessor;
    /* 0x94 */ ExplicitScopedPtr<placeholder_t> mDebugCamera;
    /* 0x98 */ ExplicitScopedPtr<placeholder_t> mMainCamera;
    /* 0x9C */ ExplicitScopedPtr<placeholder_t> mIndiviCameraManager;
    /* 0xA0 */ ExplicitScopedPtr<placeholder_t> mObjCollManager;
    /* 0xA4 */ ExplicitScopedPtr<placeholder_t> mVacuumManager;
    /* 0xA8 */ ExplicitScopedPtr<placeholder_t> mNururiManager;
    /* 0xAC */ ExplicitScopedPtr<placeholder_t> mMapMemManager;
    /* 0xB0 */ ExplicitScopedPtr<placeholder_t> mMapDecorationManager;
    /* 0xB4 */ ExplicitScopedPtr<placeholder_t> mMapLandManager;
    /* 0xB8 */ ExplicitScopedPtr<placeholder_t> mGimmickManager;
    /* 0xBC */ ExplicitScopedPtr<placeholder_t> mMoveLimit;
    /* 0xC0 */ ExplicitScopedPtr<placeholder_t> mObjGenManager;
    /* 0xC4 */ ExplicitScopedPtr<placeholder_t> mWeaponManager;
    /* 0xC8 */ ExplicitScopedPtr<placeholder_t> mHeroManager;
    /* 0xCC */ ExplicitScopedPtr<placeholder_t> mItemManager;
    /* 0xD0 */ ExplicitScopedPtr<placeholder_t> mEnemyManager;
    /* 0xD4 */ ExplicitScopedPtr<placeholder_t> mBossManager;
    /* 0xD8 */ ExplicitScopedPtr<placeholder_t> mGhostManager;
    /* 0xDC */ ExplicitScopedPtr<placeholder_t> mChallengeManager;
    /* 0xE0 */ ExplicitScopedPtr<placeholder_t> mDebugGeneralDrawer;
    /* 0xE4 */ ExplicitScopedPtr<placeholder_t> mDebugObjInfoRepos;
    /* 0xE8 */ ExplicitScopedPtr<placeholder_t> mObjPlacement;
    /* 0xEC */ ExplicitScopedPtr<placeholder_t> mShowGrid;
    /* 0xF0 */ ExplicitScopedPtr<placeholder_t> mShowPegFrame;
};

}}

#endif
