#ifndef DONUT_APP_APPLICATION_HPP
#define DONUT_APP_APPLICATION_HPP

#include <hel/common/ExplicitSingleton.hpp>
#include "app/HIDErrorMenu.hpp"
#include "msg/Manager.hpp"

namespace app {

class Application {
public:
    DECL_EXPLICIT_SINGLETON(Application);

    HIDErrorMenu& hidErrorMenu();
    msg::Manager& messageManager();
};


} // app

#endif
