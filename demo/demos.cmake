##======================================================================================================================
##  Kyosu - Complex Without Complexes
##  Copyright : KYOSU Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

## A demo opens a window, so it is never a test and no CI job runs it. raylib is pulled here rather than in
## cmake/dependencies.cmake so that a build without KYOSU_BUILD_DEMOS fetches nothing.
CPMAddPackage( NAME raylib
               GITHUB_REPOSITORY raysan5/raylib
               GIT_TAG 5.5
               OPTIONS "BUILD_EXAMPLES OFF"
                       "BUILD_SHARED_LIBS OFF"
             )

add_custom_target("kyosu-demos")

##======================================================================================================================
## Compiler options for demos
##======================================================================================================================
add_library(kyosu_demo INTERFACE)

target_compile_features(kyosu_demo INTERFACE cxx_std_20)
target_include_directories(kyosu_demo INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(kyosu_demo INTERFACE eve::eve raylib)

## What a demo has to show is the register width paying off, so it is optimised whatever the build type. The
## architecture is a separate switch: a preset that pins -mavx2 to watch a given width has to win over -march=native,
## which would otherwise silently upgrade it to whatever the host can do.
option(KYOSU_DEMO_NATIVE "Build the demos for the host architecture" ON)

if(MSVC)
  target_compile_options(kyosu_demo INTERFACE /O2)
  if(KYOSU_DEMO_NATIVE)
    target_compile_options(kyosu_demo INTERFACE /arch:AVX2)
  endif()
else()
  target_compile_options(kyosu_demo INTERFACE -O3)
  if(KYOSU_DEMO_NATIVE)
    target_compile_options(kyosu_demo INTERFACE -march=native)
  endif()
endif()

##======================================================================================================================
## Demos gather under their own target, so nothing here reaches ctest
##======================================================================================================================
## Included from the root rather than added as a subdirectory: copa_glob_unit resolves its pattern against the current
## source directory while naming targets from RELATIVE, and only the root sees both as it needs to for demo.<name>.exe.
copa_glob_unit( PATTERN "demo/*.cpp"
                RELATIVE    ${PROJECT_SOURCE_DIR}
                DESTINATION demo
                INTERFACE   kyosu_demo
                TARGET      kyosu-demos
              )
