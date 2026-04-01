#ifndef NREL_RENDER_2D_HPP
#define NREL_RENDER_2D_HPP

#include <types.h>

namespace nrel { namespace ezrender {
    class OrthoCameraSetting {
    public:
        static OrthoCameraSetting* create(f32, f32, f32, f32, f32, f32);
    };

}; // ezrender

}; //nrel

#endif
