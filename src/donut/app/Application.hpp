#ifndef DONUT_APP_APPLICATION_HPP
#define DONUT_APP_APPLICATION_HPP

#include <hel/common/ExplicitSingleton.hpp>
#include "app/HIDErrorMenu.hpp"

namespace app {

class Application {
    hel::common::ExplicitSingleton<Application> instance;
public:
    HIDErrorMenu& hidErrorMenu();
};

} // app

#endif
