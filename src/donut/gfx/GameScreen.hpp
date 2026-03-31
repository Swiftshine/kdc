#ifndef DONUT_GFX_GAMESCREEN_HPP
#define DONUT_GFX_GAMESCREEN_HPP

#include <types.h>

namespace gfx {

class GameScreen {
public:
    enum ScreenType {
        SCREEN_TYPE_FULLSCREEN,
        SCREEN_TYPE_WIDESCREEN,
    };

    GameScreen();

    u32 gameWidth() const;
    u32 gameHeight() const;

    //NOTE: is merged into GameScreen's constructor
    void setDefaultScreenType();
    //NOTE: is merged into nw4r::g3d::Camera::Camera(nw4r::g3d::CameraData*)
    void setScreenType(ScreenType type);
    //NOTE: is merged into GKI_getfirst
    ScreenType getScreenType() const;

private:
    ScreenType mScreenType;
};

}

#endif
