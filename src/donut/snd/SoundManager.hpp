#ifndef DONUT_SND_SOUNDMANAGER_HPP
#define DONUT_SND_SOUNDMANAGER_HPP

#include <hel/common/ExplicitSingleton.hpp>

namespace snd {

class SoundManager {
public:
    DECL_EXPLICIT_SINGLETON(SoundManager);

    void update();
};
}

#endif
