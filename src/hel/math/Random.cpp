#pragma peephole off
#include <hel/math/Random.hpp>

using hel::math::Random;

Random::Seed Random::Seed::Default() {
    Seed defaultSeed;
    defaultSeed.m_0 = 0x75bcd15;
    defaultSeed.m_4 = 0x159a55e5;
    defaultSeed.m_8 = 0x1f123bb5;
    defaultSeed.m_C = 0x5491333;
    return defaultSeed;
}

Random::Random(const Random::Seed& rSeed) : mSeed(rSeed) { }

bool Random::randBool(float arg1) {
    if (arg1 == 0.0f) {
        return false;
    }

    return randCoreF32() <= arg1;
}

int Random::rand(int arg1) {
    return randS32(arg1);
}

int Random::rand(int arg1, int arg2) {
    return randS32(arg1, arg2);
}

float Random::randF(float arg1, float arg2) {
    return randF32(arg1, arg2);
}

s32 Random::randS32(s32 arg1) {
    s32 coreRand = randCoreU32();
    coreRand &= 0x7FFFFFFF;
    s32 coreDivided = coreRand / arg1;
    return coreRand - coreDivided * arg1;
}

s32 Random::randS32(s32 arg1, s32 arg2) {
    return arg1 + randS32(arg2 - arg1);
}

u32 Random::randU32(u32 arg1) {
    u32 coreRand = randCoreU32();
    u32 coreDivided = coreRand / arg1;
    return coreRand - coreDivided * arg1;
}

u32 Random::randU32(u32 arg1, u32 arg2) {
    u32 coreRand = randCoreU32();

    u32 paramDifference = arg2 - arg1;
    u32 coreDivided = (coreRand / (paramDifference));
    return arg1 + (coreRand - (coreDivided * paramDifference));
}

f32 Random::randF32(f32 arg1, f32 arg2) {
    f32 coreRand = randCoreF32();

    f32 firstValue = arg2 - arg1;
    return firstValue * coreRand + arg1;
}

f32 Random::randNF() {
    return randCoreF32();
}

f32 Random::randAF() {
    return 2.0f * randCoreF32() + -1.0f;
}

u32 Random::randCoreU32() {
    u32 mSeed0 =  mSeed.m_0;
    mSeed0 ^= mSeed.m_0 << 11;
    mSeed.m_0 = mSeed.m_4;
    mSeed.m_4 = mSeed.m_8;
    mSeed.m_8 = mSeed.m_C;
    mSeed.m_C ^= mSeed.m_C >> 19;
    mSeed.m_C ^= mSeed0 ^ mSeed0 >> 8;
    return mSeed.m_C;
}

f32 Random::randCoreF32() {
    f32 randCore = randCoreU32() & 0xFFFF;
    return randCore / 65536.0f;
}
