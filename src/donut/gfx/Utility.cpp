#pragma peephole off
#include <nw4r/g3d/g3d_state.h>
#include <nrel/OrthoCameraSetting.hpp>
#include <nrel/GXSettingFor2D.hpp>
#include <nrel/ViewportSetting.hpp>
#include <nrel/Render2D.hpp>
#include <hel/math/Matrix34.hpp>
#include <hel/math/Vector3.hpp>
#include <donut/gfx/EasyRender3D.hpp>
#include <donut/gfx/Utility.hpp>
#include <donut/gfx/VISetting.hpp>
#include <donut/app/Application.hpp>

namespace gfx {
    namespace Utility {
        void SetupGXForLayout2D(f32 nearClip, f32 farClip) {
            SetupGXForLayout2D(CurrentGameWidth(), CurrentGameHeight(), nearClip, farClip);
        }

        void SetupGXForLayout2D(f32 width, f32 height, f32 nearClip, f32 farClip) {
            f32 widthHalf = 0.5f * width;
            f32 heightHalf = 0.5f * height;
            nrel::ezrender::OrthoCameraSetting camera = nrel::ezrender::OrthoCameraSetting::create(-widthHalf, heightHalf, widthHalf,
                -heightHalf, nearClip, farClip);
            nrel::ezrender::GXSettingFor2D setting2D;
            setting2D.setOrthoCameraSetting(camera);
            setting2D.setViewportSetting(RenderSetting::Instance->nrelViewportSetting());
            nrel::ezrender::Render2D::setupGX(setting2D);
        }

        void SetupGXForScreen2D(f32 nearClip, f32 farClip) {
            SetupGXForScreen2D(CurrentGameWidth(), CurrentGameHeight(), nearClip, farClip);
        }

        void SetupGXForScreen2D(f32 width, f32 height, f32 nearClip, f32 farClip) {
            //temps required for order
            f32 nearClipVal = nearClip;
            f32 farClipVal = farClip;
            f32 widthVal = width;
            f32 heightVal = height;
            nrel::ezrender::OrthoCameraSetting camera = nrel::ezrender::OrthoCameraSetting::create(0.0f, 0.0f, widthVal,
                heightVal, nearClipVal, farClipVal);

            nrel::ezrender::GXSettingFor2D setting2D;
            setting2D.setOrthoCameraSetting(camera);
            setting2D.setViewportSetting(RenderSetting::Instance->nrelViewportSetting());
            nrel::ezrender::Render2D::setupGX(setting2D);
        }

        void SetViewPort(f32 left, f32 top, f32 right, f32 bottom) {
            RenderSetting::Instance->setViewportValue(left, top, right, bottom);
        }

        u32 CurrentGameWidth() {
            return app::Application::Instance->gameScreen().gameWidth();
        }

        u32 CurrentGameHeight() {
            return app::Application::Instance->gameScreen().gameHeight();
        }

        void SetZBufferRange(f32 min, f32 max) {
            GXSetZScaleOffset(max - min, min);
        }

        //https://decomp.me/scratch/8WIZJ
        void ClearZBuffer(f32 zOffset) {
            hel::math::Matrix44 orthoMtx = hel::math::Matrix44::CreateOrtho(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f);
            EasyRender3D::SetupGX(orthoMtx, false);
            hel::math::Vector3 vec(hel::math::Vector3::BASIS_Z);
            vec.x *= -1.0f;
            vec.y *= -1.0f;
            vec.z *= -1.0f;
            hel::math::Vector3 tempLoadIG(vec);

            hel::math::Matrix34 viewMtx;
            viewMtx.CreateLookAt(hel::math::Vector3::ZERO, hel::math::Vector3::BASIS_Y, tempLoadIG);
            EasyRender3D::SetViewMtx(viewMtx);
            GXSetZScaleOffset(1.0f, 0.0f);
            GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
            GXSetColorUpdate(GX_FALSE);
            hel::math::Matrix34 mtx;
            EasyRender3D::DrawQuadFill(mtx, hel::math::Vector3(-1.0f, 1.0f, -zOffset), hel::math::Vector3(1.0f, 1.0f, -zOffset),
                hel::math::Vector3(1.0f, -1.0f, -zOffset), hel::math::Vector3(-1.0f, -1.0f, -zOffset));
            GXSetColorUpdate(GX_TRUE);

        }

        void SetGXStateDirty() {
            nw4r::g3d::G3DState::Invalidate();
        }

        void SetDimmingEnable(bool dimmingEnabled) {
            VISetting::Instance->setDimming(dimmingEnabled);
        }

        void SetRenderType(RenderSetting::Type type) {
            RenderSetting::Instance->type(type);
            RenderSetting::Instance->dirty();
        }
    }

}
