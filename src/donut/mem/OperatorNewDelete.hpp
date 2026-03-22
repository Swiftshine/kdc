#ifndef DONUT_MEM_OPERATORNEWDELETE_HPP
#define DONUT_MEM_OPERATORNEWDELETE_HPP

namespace mem {

class IAllocator;

namespace OperatorNewDelete {
    void SetDefaultAllocator(IAllocator&);
}


}

#endif
