#pragma peephole off
#include <donut/gfx/FullScreenPlate.hpp>
#include <donut/gfx/Utility.hpp>
#include <nw4r/ut.h>
#include <nrel/Render2D.hpp>

using gfx::FullScreenPlate;

FullScreenPlate::FullScreenPlate(const GXColor& rColor)
    : mColor(rColor)
    , mAlpha(1.0f)
{ }

void FullScreenPlate::draw() const {
    gfx::Utility::SetupGXForScreen2D(0.0f, 1.0f);
    f32 screenWidth = gfx::Utility::CurrentGameWidth();
    f32 screenHeight = gfx::Utility::CurrentGameHeight();
    GXColor color = mColor;
    f32 alphaVal = mColor.a * mAlpha;
    color.a = alphaVal;
    nw4r::ut::Rect screenRect(0.0f, 0.0f, screenWidth, screenHeight);
    nrel::ezrender::Render2D::renderRect(screenRect, color);
}

//NOTE: All functions below are code merged into others. Refer to the header for more details

void FullScreenPlate::setColor(const GXColor& rColor) {
    mColor.r = rColor.r;
    mColor.g = rColor.g;
    mColor.b = rColor.b;
    mColor.a = rColor.a;
}

void FullScreenPlate::setAlpha(f32 alpha) {
    mAlpha = alpha;
}
