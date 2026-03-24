#ifndef RUNTIME_GECKO_EXCEPTION_PPC_H
#define RUNTIME_GECKO_EXCEPTION_PPC_H
#include <types.h>
#include <runtime/New.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct ExtabIndexInfo;

int __register_fragment(const struct ExtabIndexInfo* extab, void* toc);
void __unregister_fragment(int i);
#ifdef __cplusplus
}
namespace std {

    class bad_exception : public exception {
    public:
        //Gets merged into std::exception::~exception()
        virtual ~bad_exception();

        virtual const char* what() const;
    };
};
#endif
#endif
