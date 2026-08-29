Installation & Quick Start {#setup}
==========================

# Pre-requisites

**KYOSU** is a header-only C++20 library. It is built on top of
[EVE](https://github.com/jfalcou/eve), which it needs at compile time and which shares its
compiler requirements:

| Compiler | Minimal version | Tested in CI |
| -------- | --------------- | ------------ |
| g++      | 13 or above     | 15           |
| clang++  | 16 or above     | 20           |

CMake 3.22 or above is required to build the tests and the documentation. Consuming the library
needs no build step of its own: adding the include directory is enough, provided EVE is reachable
too.

# Getting KYOSU

Whichever route you take, the target to link against is `kyosu::kyosu`, and EVE must be linked
alongside it. The three snippets below are the ones exercised by the integration tests, so they
are known to work.

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

`FetchContent` carries no per-package options, so the settings each dependency reads are pinned
before the call. Left out, every dependency registers its own test suite in your project.

## From an installed copy

```bash
git clone https://github.com/jfalcou/kyosu.git
cmake -S kyosu -B build -DCMAKE_INSTALL_PREFIX=/where/you/want
cmake --install build
```

then

```cmake
find_package(kyosu CONFIG REQUIRED)
target_link_libraries(my_app PUBLIC kyosu::kyosu eve::eve)
```

# Your first program

A single header brings in everything:

@godbolt{doc/quick_start.cpp}

Two things are worth noticing already. `kyosu::sqrt` is applied to a value that is not a complex
number and returns one anyway, because the square root of a negative real is not real. And the
same `kyosu::sqrt` accepts a quaternion without any change of spelling. Both are the subject of
the tutorials that follow.

# Where to go next

  + @ref tutorial-complex — complex numbers, on ground you already know.
  + @ref tutorial-simd — the same code applied to many values at once.
  + @ref tutorial-quaternion — the first algebra past the complex numbers.
  + @ref tutorial-rotation — what quaternions are actually used for.
  + @ref tutorial-options — choosing accuracy, angle units and real-only behaviour.
  + @ref tutorial-beyond — octonions, and what changes when dimensions keep doubling.

The mathematics underlying all of it is set out in @ref math_background.
