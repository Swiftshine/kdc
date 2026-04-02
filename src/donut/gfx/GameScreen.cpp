#pragma peephole off
#include <donut/gfx/GameScreen.hpp>

using gfx::GameScreen;

GameScreen::GameScreen()
    : mScreenType(SCREEN_TYPE_WIDESCREEN)
{ }

u16 GameScreen::gameWidth() const {
    if (mScreenType == SCREEN_TYPE_FULLSCREEN) {
        return 608;
    }
    return 832;
}

u16 GameScreen::gameHeight() const {
    return 456;
}

//NOTE: All functions below are code merged into others. Refer to the header for more details

void GameScreen::setDefaultScreenType() {
    mScreenType = SCREEN_TYPE_WIDESCREEN;
}

void GameScreen::setScreenType(ScreenType type) {
    mScreenType = type;
}

GameScreen::ScreenType GameScreen::getScreenType() const {
    return mScreenType;
}
