#include "scn/step/hero/Invincible.hpp"
#include "scn/step/chara/Invincible.hpp"

using namespace scn::step::hero;

Invincible::Invincible(Hero &rHero)
    : mHero(&rHero)
{
    mUnk10 = false;
    mUnk11 = false;
    mUnk12 = false;
    mUnk14 = 0;
    mUnk18 = 0;
    mUnk1C = 0;
    mUnk24 = false;
}

// https://decomp.me/scratch/o4KB6
void Invincible::update()
{
}

// https://decomp.me/scratch/czXHB
void Invincible::set(u32 frames)
{
}

void Invincible::setNoFlash(u32 frames)
{
    set(frames);
    mUnk24 = true;
}

// https://decomp.me/scratch/vaDRx
void Invincible::setPerm()
{
}

void Invincible::setPermNoFlash()
{
    setPerm();
    mUnk24 = true;
}

void Invincible::unsetPerm()
{
    if (mInvincible.mIsPerm)
    {
        mInvincible.mIsPerm = false;
        mUnk24 = false;
    }
}

void Invincible::setMighty()
{
    common::Param *pParam = mHero->param()->common();
    setMighty(pParam->mUnk4F8);
}

// https://decomp.me/scratch/Jx8Qa
void Invincible::setMighty(u32 frames)
{
    mInvincible.clear();
    mInvincible.mIsMighty = false;
}

// https://decomp.me/scratch/sL4T1
void Invincible::setMightyAfter(u32 frames)
{
	mInvincible.clear();
	mInvincible.mIsMighty = true;
}

// https://decomp.me/scratch/JGVWa
void Invincible::clearMighty()
{
	bool isMighty = mInvincible.isMighty();
}

// https://decomp.me/scratch/D5HLU
void Invincible::clear()
{
	mInvincible.clear();
	setBodyCollStateNormalIfNotMighty();

	mUnk10 = false;
	mUnk24 = false;
}

bool Invincible::getFlashOp() const
{	
	if ((mUnk11) || (mUnk18 != 0))
	{
		return true;
	}

	return false;
}

u32 Invincible::getInvincibleFrame() const
{
	return mInvincible.mFrame;
}

// https://decomp.me/scratch/3coV7
void Invincible::setBodyCollStateNormalIfNotMighty()
{		
}

// https://decomp.me/scratch/ZLpC5
void Invincible::requestMightyEffect()
{
}

// https://decomp.me/scratch/pvA7m
void Invincible::releaseMightyEffect()
{
}


