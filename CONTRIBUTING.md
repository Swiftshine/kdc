# Contributing
If you have questions or are interested in contributing, consider asking in the [GC/Wii Decompilation Discord](https://discord.gg/hKx3FJJgrV).

Sections:
- [Resources](#resources)
- [Code style](#code-style)
    - [General](#general)
    - [Headers](#headers)
    - [Files and includes](#files-and-includes)
    - [Function signatures](#function-signatures)
    - [Function parameters](#function-parameters)
    - [Function matching](#function-matching)
    - [Structures](#structures)
    - [Literals](#literals)

## Resources
- [Ghidra](https://ghidra-sre.org/) - A disassembling, decompiling, and reverse-engineering tool.
    - Using these [custom Ghidra builds](https://github.com/encounter/ghidra-ci/releases) is recommended.
- [Objdiff](https://github.com/encounter/objdiff) - A local diffing tool.

## Code style
### General
Lines should not exceed `100` characters. These can be split into multiple lines.

Use `nullptr` instead of `0` when assigning or comparing a pointer in C++.
Likewise, use `NULL` in C.
- Be explicit when comparing pointers.
    ```cpp
    // bad
    if (ptr) { }

    // good
    if (ptr != nullptr) { }
    if (ptr != NULL) { }
    ```

### Headers
Use proper header guards. HAL likes to use the `.hpp` extension for their game headers.
```cpp
#ifndef DONUT_SOME_FOLDER_MYHEADER_HPP
#define DONUT_SOME_FOLDER_MYHEADER_HPP
// ...
#endif
```

### Files and includes
For SDK, STL, and hel includes, use angled brackets. For game includes, use quotation marks.

When including files, use the full path relative to the `src` folder.

### Function Parameters
Function arguments should have certain prefixes if applicable:
- `p` for pointers
- `r` for values passed by reference

If the name of an argument is unknown, name the parameter `argX`, where `X` is the argument position:

```cpp
void MyClass::SomeFunction(int knownArg, int arg2, int arg3, int anotherKnownArg, int arg5) {
    ...
}
```

### Function Matching
If a function is not 100% matching, leave a comment in the following format above the function with a link to the associated [decomp.me](https://decomp.me) scratch. Remove it once the function has been matched.

```cpp
// https://decomp.me/scratch/EXAMPLE
void MyClass::SomeFunction() {
    ...
}
```

Before making a pull request, make sure the output of neither `ninja` nor `ninja diff` return any errors.

### Structures
Class and struct members must be prefixed with `m`.

Data entered into a class definition must be placed in the following order:
- enum and structure definitions
- `static` variables
- constructor
- destructor*
- virtual functions
- operators
- member functions
- static functions
- member variables\**

\* If the destructor is `virtual`, place it with the other virtual functions according to its position in the vtable.
E.g. if the destructor is the last function in the vtable, place it last in the
virtual function section.

\** Unless the structure is an edge-case where member variables go before the vtable.

Give descriptions of structures if it's appropriate to do so. Provide a comment describing its size.
If the size is variable, indicate so.

Offsets for fields and virtual functions relative to the start of the structure and
the start of the vtable respectively must be commented.

```cpp
class MyClass {
public:
    struct MySubstructure {
        int mSubstructureValue;
    };  

    MyClass();
    ~MyClass();

    /* 0x8 */ virtual void DoSomething();

    void DoSomethingElse();

    /* 0x4 */ int mMyValue; // If leaving comments on fields, be concise.
    /* 0x8 */ float mMyFloatValue; // e.g. "This value is for..."
};
```

Unknown fields must be referred to by their offset in hex, prefixed by an underscore.
```cpp
struct MyStruct {
    /* 0x00 */ int mKnownValue;
    /* 0x04 */ int m_4;
    /* 0x08 */ int m_8;
    /* 0x0C */ int m_C;
    /* 0x10 */ int mAnotherKnownValue;
    /* 0x14 */ int m_14;
    ...
};
```

### Literals
Be explicit for assigning and comparing floating-point values.

```cpp
// bad
float myFloat = 1;
double myDouble = 2.;

// bad
float myFloat = 1.0; // `1.0` is implicitly a double value, not a float.

// good
float myFloat = 1.0f;
double myDouble = 2.0;
```
