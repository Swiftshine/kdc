#pragma peephole off
#include <donut/mem/GlobalNewDeleteChanger.hpp>
#include <donut/mem/OperatorNewDelete.hpp>

namespace mem {
    GlobalNewDeleteChanger::GlobalNewDeleteChanger(IAllocator& rAllocator)
        : mAllocator(rAllocator)
    {
        OperatorNewDelete::SetGlobalNewDeleteAllocator(rAllocator);
    }

    GlobalNewDeleteChanger::~GlobalNewDeleteChanger() {
        OperatorNewDelete::UnsetGlobalNewDeleteAllocator(mAllocator);
    }
}
