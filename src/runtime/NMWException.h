#ifndef NMWEXCEPTION_H
    #define NMWEXCEPTION_H

    typedef void* ctor_dtor_ptr;
    #include <types.h>

    #ifdef __cplusplus
        extern "C" {
    #endif

    void* __construct_new_array(void *, ctor_dtor_ptr, ctor_dtor_ptr, size_t, size_t);
    void __construct_array(void *, ctor_dtor_ptr, ctor_dtor_ptr, size_t, size_t);
    void __destroy_arr(void *, ctor_dtor_ptr, size_t, size_t);
    void __destroy_new_array(void *, ctor_dtor_ptr);
    char __throw_catch_compare(const char *throwtype, const char *catchtype, long *offset_result);
    #ifdef __cplusplus
        };
    #endif

    namespace std {
        typedef void (*terminate_handler)();

        extern void terminate();
        extern void unexpected();
    }
#endif
