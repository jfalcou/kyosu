Installation {#setup}
============

# Prerequisites

**KYOSU** is a header-only C++20 library with the following requirements:

| Compiler | Minimal version | Tested in CI          |
| -------- | --------------- | --------------------- |
| g++      | 13 or above     | 15                    |
| clang++  | 16 or above     | 19, and Apple clang   |

It depends on:

  + [EVE](https://github.com/jfalcou/eve), at compile time, for the SIMD types and the real
    functions.
  + CMake 3.22 or above, for the tests and the documentation only.

A consumer has no build step: the include directory of the library and the one of EVE are
enough.

# Installation

The target to link is `kyosu::kyosu`, with `eve::eve` beside it.

## With CPM

```cmake
CPMAddPackage ( NAME kyosu
                GIT_REPOSITORY "https://github.com/jfalcou/kyosu.git"
                GIT_TAG main
                OPTIONS "KYOSU_BUILD_TEST OFF"
              )

target_link_libraries(my_app PUBLIC kyosu::kyosu eve::eve)
```

## With FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(kyosu GIT_REPOSITORY "https://github.com/jfalcou/kyosu.git" GIT_TAG main)
FetchContent_Declare(eve   GIT_REPOSITORY "https://github.com/jfalcou/eve.git"   GIT_TAG main)

set(KYOSU_BUILD_TEST        OFF CACHE BOOL "" FORCE)
set(EVE_BUILD_TEST          OFF CACHE BOOL "" FORCE)
set(EVE_BUILD_BENCHMARKS    OFF CACHE BOOL "" FORCE)
set(EVE_BUILD_DOCUMENTATION OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(kyosu)
FetchContent_MakeAvailable(eve)

target_link_libraries(my_app PUBLIC kyosu::kyosu eve::eve)
```

## With a git clone

```bash
git clone https://github.com/jfalcou/kyosu.git
cmake -S kyosu -B build -DCMAKE_INSTALL_PREFIX=<prefix>
cmake --install build
```

then

```cmake
find_package(kyosu CONFIG REQUIRED)
target_link_libraries(my_app PUBLIC kyosu::kyosu eve::eve)
```

# First program

`kyosu/kyosu.hpp` declares every type and every function of the library. A program that
includes it and links `kyosu::kyosu` as above compiles and runs:

@godbolt{doc/quick_start.cpp}

# Tutorials

  + @ref tutorial-complex "Complex numbers"
  + @ref tutorial-simd "SIMD support"
  + @ref tutorial-quaternion "Quaternions"
  + @ref tutorial-beyond "Octonions and higher algebras"
  + @ref tutorial-rotation "Rotations"
  + @ref tutorial-options "Options"

The construction itself, and the theorems behind what the higher dimensions lose, are set out in
@ref math_background.
