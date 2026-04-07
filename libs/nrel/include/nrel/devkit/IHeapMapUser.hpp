#ifndef NREL_INTERFACE_HEAP_MAP_USER_HPP
#define NREL_INTERFACE_HEAP_MAP_USER_HPP

namespace nrel { namespace devkit { namespace heapmap {
    class IHeapMapUser {
    public:
        IHeapMapUser();
        //NOTE: Merged into scn::IScene::~IScene()
        /* 0x8 */ virtual ~IHeapMapUser();

    };


}; //heapmap

}; // devkit

}; //nrel

#endif
