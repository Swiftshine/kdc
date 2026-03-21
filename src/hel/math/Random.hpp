#ifndef HEL_MATH_RANDOM_HPP
#define HEL_MATH_RANDOM_HPP

#include <nw4r/math.h>

namespace hel  { namespace math {
    class Random {
    public:
        class Seed {
        public:
            static Seed Default();

            /* 0x0 */ s32 m_0;
            /* 0x4 */ s32 m_4;
            /* 0x8 */ s32 m_8;
            /* 0xC */ u32 m_C;
        };

        Random(const Seed& rSeed);

        //Is folded into rand(int)
        int operator()(int arg1) {
            return randS32(arg1);
        }

        bool randBool(float);
        int rand(int);
        int rand(int, int);
        float randF(float, float);
        s32 randS32(s32);
        s32 randS32(s32, s32);
        u32 randU32(u32);
        u32 randU32(u32, u32);
        f32 randF32(f32, f32);
        f32 randNF();
        f32 randAF();
        //Note: may be private
        u32 randCoreU32();
        f32 randCoreF32();

        /* 0x0 */ Seed mSeed;
    };

} //namespace math

} //namespace hel
#endif
