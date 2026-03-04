#ifndef DONUT_PARAM_JITPARAM_HPP
#define DONUT_PARAM_JITPARAM_HPP

#include "xdata/XData.hpp"
#include "util/PlacementNew.hpp"

namespace param {

    class ParamAccessor {
    public:
        ~ParamAccessor();

        inline xdata::XData* get() { // unofficial name
            return reinterpret_cast<xdata::XData*>(
                reinterpret_cast<u8*>(&mXData) + 4
            );
        }
    private:
    friend class JITParam;
        xdata::XData* mXData;
    };

    class JITParam {
    public:
        JITParam(const char* pParamName);
        ~JITParam();

        void loadCheck() const;

        template <typename T>
        const T& data() const;
        /* 0x0 */ const char* mParamName;
        /* 0x4 */ ParamAccessor* mAccessor;
        STRUCT_FILL(8);
    };

}

#endif
