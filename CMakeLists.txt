##======================================================================================================================
##  Kyosu - Complex Without Complexes
##  Copyright : KYOSU Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(kyosu LANGUAGES CXX)
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)

##======================================================================================================================

##======================================================================================================================
## Project setup via copacabana
##======================================================================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${COPACABANA_SOURCE_DIR}/copacabana/cmake)
include(${COPACABANA_SOURCE_DIR}/copacabana/cmake/copacabana.cmake)

copa_add_option(KYOSU_USE_PCH "Build tests with precompiled headers" ON LABEL "Use PCH")
copa_add_option(KYOSU_BUILD_TEST "Build tests for KYOSU" ON LABEL "Unit tests")
copa_add_option(KYOSU_BUILD_DOCUMENTATION "Build Doxygen for KYOSU" OFF LABEL "Doxygen")
copa_add_option(KYOSU_ENABLE_SANITIZERS "Build tests with AddressSanitizer + UndefinedBehaviorSanitizer" OFF LABEL "Sanitizers")
copa_add_option(KYOSU_ENABLE_COVERAGE "Build tests with code coverage instrumentation" OFF LABEL "Coverage")
copa_add_option(KYOSU_BUILD_DEMOS "Build the interactive demos" OFF LABEL "Demos")
copa_project_version(MAJOR 0 MINOR 1 PATCH 0 REPOSITORY https://github.com/jfalcou/kyosu)

##======================================================================================================================
## Summary Display
##======================================================================================================================
copa_show_options()

if(NOT KYOSU_QUIET)
  set(QUIET_OPTION "")
else()
  set(QUIET_OPTION "QUIET")
endif()

copa_setup_precommit_hooks(${QUIET_OPTION})

##======================================================================================================================
## Install Process setup
##======================================================================================================================
copa_setup_install( LIBRARY kyosu
                    FEATURES cxx_std_20
                    DOC     ${PROJECT_SOURCE_DIR}/LICENSE.md
                    INCLUDE ${PROJECT_SOURCE_DIR}/include/kyosu
                  )

##======================================================================================================================
## Setup doxygen
##======================================================================================================================
if(KYOSU_BUILD_DOCUMENTATION)
  copa_setup_doxygen(${QUIET_OPTION}
                     DESTINATION "${PROJECT_BINARY_DIR}/doc"
                     GODBOLT_LIBRARIES kyosu eve
                     GODBOLT_COMPILER clang2010
                     GODBOLT_OPTIONS "-O3 -std=c++20 -DNDEBUG"
                     COLOR_HUE 232
                     COLOR_SATURATION 57
                     COLOR_LIGHTNESS 28
                     TAGFILES eve=https://jfalcou.github.io/eve)

endif()

##======================================================================================================================
## Setup PCH
##======================================================================================================================
copa_setup_pch( TARGET kyosu        INTERFACES  kyosu_test  HEADERS include/kyosu/kyosu.hpp)
copa_setup_pch( TARGET kyosu_doc    INTERFACES  kyosu_docs  HEADERS include/kyosu/kyosu.hpp)
copa_setup_pch( TARGET kyosu_bench  INTERFACES  kyosu_bench HEADERS include/kyosu/kyosu.hpp)

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(KYOSU_BUILD_TEST)
  if(KYOSU_ENABLE_SANITIZERS)
    copa_setup_sanitizers(kyosu_docs ENABLE_ASAN ENABLE_UBSAN)
  endif()

  enable_testing()
  add_subdirectory(test)

  # After the test targets exist, so the coverage targets can depend on them
  if(KYOSU_ENABLE_COVERAGE)
    copa_setup_coverage(kyosu_docs)
  endif()
endif()

##======================================================================================================================
## Demos setup - they open a window, so no CI job builds them
##======================================================================================================================
if(KYOSU_BUILD_DEMOS)
  include(${PROJECT_SOURCE_DIR}/demo/demos.cmake)
endif()
