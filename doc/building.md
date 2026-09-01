Building for Testing {#building}
====================

This page is for working on **KYOSU** itself. Consuming it from another project needs none of
this and is covered in @ref setup.

# CMake setup

Use a preset. `CMakePresets.json` carries the configurations the CI judges a pull request on, so
a preset reproduces one of them exactly rather than approximating it:

| Preset | Configuration |
| ------ | ------------- |
| `gcc`, `clang` | the compiler, everything else left alone |
| `gcc-avx2`, `clang-avx2` | the same with AVX2 enabled |
| `gcc-no-pch` | without the precompiled header, which is what catches a missing include |
| `gcc-sanitize`, `clang-sanitize` | AddressSanitizer and UndefinedBehaviorSanitizer |
| `gcc-coverage`, `clang-coverage` | coverage instrumentation |
| `gcc-bench`, `clang-bench` | the benchmarks rather than the tests |
| `gcc-demos`, `clang-demos` | the interactive demos |
| `clang-macos`, `clang-macos-libc++` | macOS, against libstdc++ and libc++ |

```bash
cmake --preset=gcc
```

Each also settles the generator, a build directory named after itself, and `Debug` as the
configuration built by default. The compilers they name are the ones in the CI image, which is
published as a Docker image and described on
[EVE's development environment page](https://jfalcou.github.io/eve/dev_environment.html).

Without one, the equivalent by hand is:

```bash
cmake -S . -B build -G Ninja \
      -DCMAKE_CXX_COMPILER=g++ \
      -DCMAKE_CXX_FLAGS="-O0 -DEVE_NO_FORCEINLINE"
```

`EVE_NO_FORCEINLINE` is the flag worth knowing about there. It takes the forced inlining off
EVE's functions, which the tests do not need and which otherwise dominates their compilation
time. `clang++` works in place of `g++`, and any version meeting the requirements in @ref setup.

Six options steer what gets declared, and the presets set them for you:

| Option | Default | Effect |
| ------ | ------- | ------ |
| `KYOSU_BUILD_TEST` | `ON` | declare the test targets |
| `KYOSU_USE_PCH` | `ON` | build the tests against a precompiled header |
| `KYOSU_BUILD_DOCUMENTATION` | `OFF` | declare the `kyosu-doxygen` target |
| `KYOSU_ENABLE_SANITIZERS` | `OFF` | AddressSanitizer and UndefinedBehaviorSanitizer |
| `KYOSU_ENABLE_COVERAGE` | `OFF` | coverage instrumentation |
| `KYOSU_BUILD_DEMOS` | `OFF` | build the interactive demos |

# Compiling the tests

The tests are named targets rather than part of `all`, so `--target all` builds nothing. The
whole suite is `kyosu-test`, and below it every directory of `test/` has a target of its own,
named after its path with the separators turned into dots:

| Target | Content |
| ------ | ------- |
| `kyosu-test` | everything below, 493 tests |
| `unit.exe` | all unit tests |
| `unit.complex.exe` | complex-specific unit tests |
| `unit.quaternion.exe` | quaternion-specific unit tests |
| `unit.function.exe` | unit tests of the functions over any algebra |
| `unit.infra.exe` | unit tests of the infrastructure itself |
| `doc.exe` | every example that appears in the documentation |
| `doc.<function>.exe` | the examples of one function, `doc.sqrt.exe` and so on |

For example, the unit test of `kyosu::acos` over complex numbers is one file, and it compiles
on its own:

```bash
ninja -C build unit.complex.acos.exe
```

`unit.exe` and `kyosu-test` are very large and want a comfortable number of cores. Working on a
single function is almost always a matter of building its own target rather than either of them.

# Running the tests

The executables land in `build/unit`, and each can be run directly:

```bash
./build/unit/unit.complex.acos.exe
```

`ctest` runs them all, and takes the same preset as the build:

```bash
ctest --test-dir build
ctest --preset=gcc
```

# Building the documentation

```bash
cmake -S . -B build -G Ninja -DKYOSU_BUILD_TEST=OFF -DKYOSU_BUILD_DOCUMENTATION=ON
cmake --build build --target kyosu-doxygen
```

The pages land in `build/doc`. EVE's tagfile is downloaded while configuring, which is what makes
the `eve::` references resolve; with no network they degrade to plain text and a warning says so.
