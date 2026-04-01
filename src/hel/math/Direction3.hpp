#ifndef HEL_MATH_DIRECTION3_HPP
#define HEL_MATH_DIRECTION3_HPP

#include <nw4r/math.h>
#include <hel/math/Vector3.hpp>
namespace hel { namespace math {
    class Direction3 {
    public:

        class Left {
            bool permittedRestruct();
            void restruct();

            /* 0x0 */ Direction3* mDirection;
        };

        class Up {
            bool permittedRestruct();
            void restruct();

            /* 0x0 */ Direction3* mDirection;
        };

        class Front {
            bool permittedRestruct();
            void restruct();

            /* 0x0 */ Direction3* mDirection;
        };

        static Direction3 BASIS;
        static Direction3 FRONT_TO_RIGHT;
        static Direction3 FRONT_TO_LEFT;

        Direction3();
        Direction3(const Direction3& rOther);
        Direction3(const Vector3& rFront, const Vector3& rUp, const Vector3& rLeft);

        void operator=(const Direction3& rOther);

        void normalize();

        /* 0x00 */ Vector3 mFront;
        /* 0x0C */ Vector3 mUp;
        /* 0x18 */ Vector3 mLeft;
    };
} // math

} // hel

#endif
