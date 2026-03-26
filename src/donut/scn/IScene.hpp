#ifndef DONUT_SCN_ISCENE_HPP
#define DONUT_SCN_ISCENE_HPP

#include "scn/DrawReqInfo.hpp"

namespace scn {
    class IScene {
    public:
        /* 0x08 */ virtual void GetRuntimeTypeInfo();
        /* 0x0C */ virtual ~IScene() { }
        /* 0x10 */ virtual void updateMain();
        /* 0x14 */ virtual void updateUseGPU();
        /* 0x18 */ virtual void updateUseDebug();
        /* 0x1C */ virtual void draw(const DrawReqInfo&);
        /* 0x20 */ virtual bool isSceneEnd() const;
    };
}

#endif
