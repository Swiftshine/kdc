#ifndef DONUT_UTIL_PLACEMENTNEW_HPP
#define DONUT_UTIL_PLACEMENTNEW_HPP

namespace util {
    template <typename T>
    class PlacementNew {
    public:
        ~PlacementNew();

        PlacementNew();

        inline operator T*() {
            return ptr;
        }

        inline T* operator->() {
            return ptr;
        }

        inline const T* operator->() const {
            return ptr;
        }
        void destruct();
    private:
        T* ptr;
    };
}

#endif
