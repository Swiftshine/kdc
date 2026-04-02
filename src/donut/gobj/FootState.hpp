#ifndef DONUT_GOBJ_FOOT_STATE_HPP
#define DONUT_GOBJ_FOOT_STATE_HPP

namespace gobj {

class FootState {
public:
    //NOTE: Merged into file::DNOption::DNOption()
    FootState();


    bool isAir() const;
    //NOTE: Merged into effect::detail::GenContext::dataType() const
    bool isGround() const;

    //NOTE: Merged into file::DNOption::DNOption()
    void setAir();
    void setGround();

    /* 0x0 */ bool mOnGround;
};
}

#endif
