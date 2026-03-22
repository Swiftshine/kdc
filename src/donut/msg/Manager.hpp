#ifndef DONUT_MSG_MANAGER_HPP
#define DONUT_MSG_MANAGER_HPP

#include <types.h>

namespace msg {

class Manager {
public:
    enum Category {
        CAT_NAME,
        CAT_LVMAP,
        CAT_SHIP,
        CAT_STEP,
        CAT_CHALLENGE,
        CAT_CHALLENGETITLE,
        CAT_CHALLENGEFILESELECT,
        CAT_PAUSE,
        CAT_COMMON,
        // CAT_TITLEMENU, // unused
        CAT_OPTION,
        CAT_HISTORY,
        CAT_PRODUCT,
        CAT_NEWS,
        CAT_PLAYMOVIE,
        CAT_RESIDENT,
        CAT_GRANDMENU,
        CAT_GRANDTITLE,
        CAT_STAFFCREDIT,
    };

    Manager();
    ~Manager();

    const char* text(Category category, const char* pText);
    const char* unsafedText(Category category, const char* pText);

private:
    STRUCT_FILL(0x1A8);
};
}

#endif
