#ifndef DONUT_APP_SAVEINFO_HPP
#define DONUT_APP_SAVEINFO_HPP

#include <types.h>

namespace app {
class ResidentFile;

class SaveInfo {
public:
    SaveInfo(ResidentFile&);
    ~SaveInfo();

    void afterSceneDestroy(bool);
    void update();
    void draw();
private:
    STRUCT_FILL(0x3B8);
};

}

#endif
