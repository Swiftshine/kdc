#ifndef DONUT_APP_APPLICATION_HPP
#define DONUT_APP_APPLICATION_HPP

#include <hel/common/ExplicitSingleton.hpp>
#include <donut/app/HIDErrorMenu.hpp>
#include <donut/msg/Manager.hpp>
#include <donut/gfx/GameScreen.hpp>
#include <donut/preload/PreLoadManager.hpp>
#include <donut/file/FileManager.hpp>

namespace app {

class Application {
public:
    DECL_EXPLICIT_SINGLETON(Application);

    HIDErrorMenu& hidErrorMenu();
    msg::Manager& messageManager();
    gfx::GameScreen& gameScreen();
    preload::PreLoadManager& preLoadManager();
    file::FileManager& fileManager();
};


} // app

#endif
