#include <revolution/OS.h>
#include <runtime/Gecko_ExceptionPPC.h>

#define NUM_FRAGMENT 32

typedef struct FragmentInfo {
    const ExtabIndexInfo* eti; // at 0x0
    void* toc;                 // at 0x4
    BOOL regist;               // at 0x8
} FragmentInfo;

static FragmentInfo fragmentInfo[NUM_FRAGMENT];

int __register_fragment(const ExtabIndexInfo* eti, void* toc) {
    FragmentInfo* frag;
    int i;

    for (i = 0, frag = fragmentInfo; i < NUM_FRAGMENT; i++, ++frag) {

        if (!frag->regist) {
            frag->eti = eti;
            frag->toc = toc;
            frag->regist = TRUE;
            return i;
        }
    }

    return -1;
}

void __unregister_fragment(int i) {
    FragmentInfo* frag;

    if (i >= 0 && i < NUM_FRAGMENT) {
        frag = &fragmentInfo[i];
        frag->eti = NULL;
        frag->toc = NULL;
        frag->regist = FALSE;
    }
}

namespace std {
    bad_exception::~bad_exception() {}

    const char* bad_exception::what() const {
        return "bad_exception";
    }
};
