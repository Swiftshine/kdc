#ifndef HEL_COMMON_NONCOPYABLE_HPP
#define HEL_COMMON_NONCOPYABLE_HPP

namespace hel { namespace common {

class NonCopyable {
public:
    NonCopyable() { }
private:
    NonCopyable(const NonCopyable& rOther);
};

}}

#endif
