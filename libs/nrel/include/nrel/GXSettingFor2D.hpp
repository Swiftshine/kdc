#ifndef NREL_GX_SETTING_2D_HPP
#define NREL_GX_SETTING_2D_HPP

#include <nrel/OrthoCameraSetting.hpp>
#include <nrel/ViewportSetting.hpp>

namespace nrel { namespace ezrender {
    class OrthoCameraSetting;
    class ViewportSetting;

    class GXSettingFor2D {
    public:

        GXSettingFor2D();

        //NOTE: Merged into scn::IScene::~IScene()
        ~GXSettingFor2D();

        void setOrthoCameraSetting(const OrthoCameraSetting&);
        void setViewportSetting(const ViewportSetting&);

        /* 0x00 */ OrthoCameraSetting mCameraSetting;
        /* 0x18 */ ViewportSetting  mViewportSetting;
    };

}; // ezrender

}; //nrel

#endif
