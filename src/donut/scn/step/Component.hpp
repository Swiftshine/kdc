#ifndef DONUT_SCN_STEP_COMPONENT_HPP
#define DONUT_SCN_STEP_COMPONENT_HPP

#include <hel/common/ScopedPtr.hpp>
#include "scn/step/Context.hpp"
#include "scn/step/core/SphereAccessor.hpp"
#include "scn/step/map/DataFile.hpp"
#include "scn/step/debug/ShowGrid.hpp"
#include "scn/step/debug/ShowPegFrame.hpp"
#include "scn/step/debug/GeneralDrawer.hpp"
#include "scn/step/debug/ObjInfoRepos.hpp"

using hel::common::ScopedPtr;

namespace scn { namespace step {

class Component {
private:
    typedef int placeholder_t;
public:
    debug::GeneralDrawer* debugGeneralDrawer();
    debug::ObjInfoRepos* debugObjInfoRepos();
private:
    /* 0x00 */ ScopedPtr<Context> mContext;
    /* 0x04 */ ScopedPtr<map::DataFile> mDataFile;
    /* 0x08 */ ScopedPtr<core::SphereAccessor> mSphereAccessor;
    /* 0x0C */ ScopedPtr<placeholder_t> mSceneChanger;
    /* 0x10 */ ScopedPtr<placeholder_t> mResFileRepository;
    /* 0x14 */ ScopedPtr<placeholder_t> mG3DRootSet;
    /* 0x18 */ ScopedPtr<placeholder_t> mEffectManager;
    /* 0x1C */ ScopedPtr<placeholder_t> mAreaLightManager;
    /* 0x20 */ ScopedPtr<placeholder_t> mMintManager;
    /* 0x24 */ ScopedPtr<placeholder_t> mRumbleManager;
    /* 0x28 */ ScopedPtr<placeholder_t> mPermSoundSE;
    /* 0x2C */ ScopedPtr<placeholder_t> mAreaOperation;
    /* 0x30 */ ScopedPtr<placeholder_t> mBGMController;
    /* 0x34 */ ScopedPtr<placeholder_t> mPauseTrigger;
    /* 0x38 */ ScopedPtr<placeholder_t> mOstopManager;
    /* 0x3C */ ScopedPtr<placeholder_t> mSuperStopManager;
    /* 0x40 */ ScopedPtr<placeholder_t> mPermEffect;
    /* 0x44 */ ScopedPtr<placeholder_t> mPreLoadReq;
    /* 0x48 */ ScopedPtr<placeholder_t> mBgFadeWithoutLand;
    /* 0x4C */ ScopedPtr<placeholder_t> mBgFade;
    /* 0x50 */ ScopedPtr<placeholder_t> mBgFadeOverGimmick;
    /* 0x54 */ ScopedPtr<placeholder_t> mFgFade;
    /* 0x58 */ ScopedPtr<placeholder_t> mScreenFade;
    /* 0x5C */ ScopedPtr<placeholder_t> mWip;
    /* 0x60 */ ScopedPtr<placeholder_t> mCinemaScope;
    /* 0x64 */ ScopedPtr<placeholder_t> mAbilityGetFade;
    /* 0x68 */ ScopedPtr<placeholder_t> mSuperFade;
    /* 0x6C */ ScopedPtr<placeholder_t> mSuperBackPicture;
    /* 0x70 */ ScopedPtr<placeholder_t> mSfxManager;
    /* 0x74 */ ScopedPtr<placeholder_t> mShadowRoot;
    /* 0x78 */ ScopedPtr<placeholder_t> mDarknessRoot;
    /* 0x7C */ ScopedPtr<placeholder_t> mDarknessAdjust;
    /* 0x80 */ ScopedPtr<placeholder_t> mInfoManager;
    /* 0x84 */ ScopedPtr<placeholder_t> mPauseManager;
    /* 0x88 */ ScopedPtr<placeholder_t> mCameraController;
    /* 0x8C */ ScopedPtr<placeholder_t> mBgCamera;
    /* 0x90 */ ScopedPtr<placeholder_t> mCameraAccessor;
    /* 0x94 */ ScopedPtr<placeholder_t> mDebugCamera;
    /* 0x98 */ ScopedPtr<placeholder_t> mMainCamera;
    /* 0x9C */ ScopedPtr<placeholder_t> mIndiviCameraManager;
    /* 0xA0 */ ScopedPtr<placeholder_t> mObjCollManager;
    /* 0xA4 */ ScopedPtr<placeholder_t> mVacuumManager;
    /* 0xA8 */ ScopedPtr<placeholder_t> mNururiManager;
    /* 0xAC */ ScopedPtr<placeholder_t> mMapMemManager;
    /* 0xB0 */ ScopedPtr<placeholder_t> mMapDecorationManager;
    /* 0xB4 */ ScopedPtr<placeholder_t> mMapLandManager;
    /* 0xB8 */ ScopedPtr<placeholder_t> mGimmickManager;
    /* 0xBC */ ScopedPtr<placeholder_t> mMoveLimit;
    /* 0xC0 */ ScopedPtr<placeholder_t> mObjGenManager;
    /* 0xC4 */ ScopedPtr<placeholder_t> mWeaponManager;
    /* 0xC8 */ ScopedPtr<placeholder_t> mHeroManager;
    /* 0xCC */ ScopedPtr<placeholder_t> mItemManager;
    /* 0xD0 */ ScopedPtr<placeholder_t> mEnemyManager;
    /* 0xD4 */ ScopedPtr<placeholder_t> mBossManager;
    /* 0xD8 */ ScopedPtr<placeholder_t> mGhostManager;
    /* 0xDC */ ScopedPtr<placeholder_t> mChallengeManager;
    /* 0xE0 */ ScopedPtr<debug::GeneralDrawer> mDebugGeneralDrawer;
    /* 0xE4 */ ScopedPtr<debug::ObjInfoRepos> mDebugObjInfoRepos;
    /* 0xE8 */ ScopedPtr<placeholder_t> mObjPlacement;
    /* 0xEC */ ScopedPtr<debug::ShowGrid> mShowGrid;
    /* 0xF0 */ ScopedPtr<debug::ShowPegFrame> mShowPegFrame;
};

}}

#endif
