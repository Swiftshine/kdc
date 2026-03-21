#include <math/Random.hpp>

using hel::math::Random;

Random::Seed Random::Seed::Default() {
    Seed defaultSeed;
    defaultSeed._0 = 0x75bcd15;
    defaultSeed._4 = 0x159a55e5;
    defaultSeed._8 = 0x1f123bb5;
    defaultSeed._C = 0x5491333;
    return defaultSeed;
}

Random::Random(const Random::Seed& seed) : mSeed(seed) { }

//93.04% matching https://decomp.me/scratch/7ceBP
//psq_l instead of psq_lx
bool Random::randBool(float param1) {
    if (param1 == 0.0f) {
        return false;
    }

    return randCoreF32() <= param1;
}

int Random::rand(int param1) {
    return randS32(param1);
}

int Random::rand(int param1, int param2) {
    return randS32(param1, param2);
}

float Random::randF(float param1, float param2) {
    return randF32(param1, param2);
}

s32 Random::randS32(s32 param1) {
    s32 coreRand = randCoreU32();
    coreRand &= 0x7FFFFFFF;
    s32 coreDivided = coreRand / param1;
    return coreRand - coreDivided * param1;
}

s32 Random::randS32(s32 param1, s32 param2) {
    return param1 + randS32(param2 - param1);
}

u32 Random::randU32(u32 param1) {
    u32 coreRand = randCoreU32();
    u32 coreDivided = coreRand / param1;
    return coreRand - coreDivided * param1;
}

u32 Random::randU32(u32 param1, u32 param2) {
    u32 coreRand = randCoreU32();

    u32 paramDifference = param2 - param1;
    u32 coreDivided = (coreRand / (paramDifference));
    return param1 + (coreRand - (coreDivided * paramDifference));
}

//85.45% matching https://decomp.me/scratch/EXBhR
//psq_l instead of psq_lx
f32 Random::randF32(f32 param1, f32 param2) {
    f32 coreRand = randCoreF32();

    f32 firstValue = param2 - param1;
    return firstValue * coreRand + param1;
}

f32 Random::randNF() {
    return randCoreF32();
}

f32 Random::randAF() {
    return 2.0f * randCoreF32() + -1.0f;
}

//96.47% matching https://decomp.me/scratch/W3R5t
//swrai instead of swri
u32 Random::randCoreU32() {
    u32 mSeed0 =  mSeed._0;
    mSeed0 ^= mSeed._0 << 11;
    mSeed._0 = mSeed._4;
    mSeed._4 = mSeed._8;
    mSeed._8 = mSeed._C;
    mSeed._C ^= mSeed._C >> 19;
    mSeed._C ^= mSeed0 ^ mSeed0 >> 8;
    return mSeed._C;
}

f32 Random::randCoreF32() {
    f32 randCore = randCoreU32() & 0xFFFF;
    return randCore / 65536.0f;
}
