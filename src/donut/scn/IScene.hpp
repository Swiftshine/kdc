#ifndef DONUT_SCN_ISCENE_HPP
#define DONUT_SCN_ISCENE_HPP

namespace scn {
    class IScene {
    public:
        /* 0x08 */ virtual ~IScene() { }
        /* 0x0C */ virtual void vfC();
        /* 0x10 */ virtual void vf10();
        /* 0x14 */ virtual void vf14();
        /* 0x18 */ virtual void vf18();
        /* 0x1C */ virtual void vf1C();
        /* 0x20 */ virtual bool vf20() const;
    };
}

#endif
