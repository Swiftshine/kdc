#ifndef HEL_COMMON_PROTECTED_SINGLETON_HPP
#define HEL_COMMON_PROTECTED_SINGLETON_HPP

namespace hel { namespace common {

template <typename T>
class ProtectedSingleton {
public:
    virtual ~ProtectedSingleton();
protected:
    static T* ptr_;
};
}}

#endif
