#ifndef DONUT_APP_RESET_HPP
#define DONUT_APP_RESET_HPP

#include <types.h>
#include <hel/common/ExplicitSingleton.hpp>
namespace app {

class Reset : public hel::common::ExplicitSingleton<Reset> {
public:
    Reset();
    ~Reset();
private:
    STRUCT_FILL(0x54);
};

}

#endif
