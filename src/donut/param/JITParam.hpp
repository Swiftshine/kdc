#ifndef DONUT_PARAM_JITPARAM_HPP
#define DONUT_PARAM_JITPARAM_HPP

#include "xdata/XData.hpp"

namespace param {

class ParamAccessor {
public:

private:
friend class JITParam;
    int m_0;
    xdata::XDataHeader* mXData;
};

class JITParam {
public:
    JITParam(const char* pParamName);
    ~JITParam();

    void loadCheck() const;

    template <typename T>
    const T& data() const;
private:
    /* 0x0 */ const char* mParamName;
    /* 0x4 */ ParamAccessor* mAccessor;
};

}

#endif
