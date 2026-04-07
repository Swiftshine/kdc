#ifndef DONUT_MEM_HEAP_MAP_USER_REPOS_HPP
#define DONUT_MEM_HEAP_MAP_USER_REPOS_HPP

#include <types.h>

namespace nrel { namespace devikit { namespace heapmap {
    class IHeapMapUser;
}}};

namespace mem {
    namespace HeapMapUserRepos {
        void Register(nrel::devikit::heapmap::IHeapMapUser& rUser);
        void Unregister(nrel::devikit::heapmap::IHeapMapUser& rUser);
    };

}

#endif
