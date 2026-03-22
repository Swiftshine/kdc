#ifndef DONUT_FONT_FONTMANAGER_HPP
#define DONUT_FONT_FONTMANAGER_HPP

#include <types.h>

namespace font {

class FontManager {
public:
    FontManager();
    ~FontManager();
private:
    STRUCT_FILL(0x8C);
};

}

#endif
