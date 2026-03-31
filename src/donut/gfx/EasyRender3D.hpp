#ifndef DONUT_GFX_EASY_RENDER_3D_HPP
#define DONUT_GFX_EASY_RENDER_3D_HPP

#include <revolution/GX.h>

namespace hel { namespace math {
    class Matrix44;
    class Matrix34;
    class Vector3;
}

};

namespace gfx {

    namespace EasyRender3D {
        void SetupGX(const hel::math::Matrix44&, bool);
        void SetColor(const GXColor&);
        void SetViewMtx(const hel::math::Matrix34&);
        void DrawCircleFill(const hel::math::Matrix34&, f32, f32, const hel::math::Vector3&, const hel::math::Vector3&);
        void DrawQuadFill(const hel::math::Matrix34&, const hel::math::Vector3&, const hel::math::Vector3&,
            const hel::math::Vector3&, const hel::math::Vector3&);
        void DrawStarFill(const hel::math::Matrix34&, f32, f32, f32, const hel::math::Vector3&,
            const hel::math::Vector3&);
        void DrawLine(const hel::math::Matrix34&, const hel::math::Vector3&,
            const hel::math::Vector3&, f32);
    };
}

#endif
