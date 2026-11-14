##======================================================================================================================
##  Kyosu - Complex Without Complexes
##  Copyright : KYOSU Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## Take the dependencies from the environment, without CPM
##======================================================================================================================
option(KYOSU_EXTERNAL_DEPENDENCIES "Take dependencies from the environment instead of fetching them" OFF)

##======================================================================================================================
## Retrieve a package declared below, from the environment or by CPM
##======================================================================================================================
macro(kyosu_get_package name)
  if(KYOSU_EXTERNAL_DEPENDENCIES)
    find_package(${name} CONFIG REQUIRED)
  else()
    CPMGetPackage(${name})
  endif()
endmacro()

if(KYOSU_EXTERNAL_DEPENDENCIES)
  if(NOT COPACABANA_SOURCE_DIR)
    message(FATAL_ERROR "[KYOSU] - KYOSU_EXTERNAL_DEPENDENCIES needs COPACABANA_SOURCE_DIR")
  endif()
  find_package(EVE CONFIG REQUIRED)
  return()
endif()

##======================================================================================================================
## CPM is vendored rather than fetched: file(DOWNLOAD) reports nothing on a failure, so a network
## hiccup leaves an empty file and CMake only complains later that CPMAddPackage does not exist.
##======================================================================================================================
include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

##======================================================================================================================
## Retrieve dependencies
##
## This file runs before the project can declare an option, copa_add_option arriving with copacabana, so a package
## wanted only under an option is declared here and fetched after the options, in CMakeLists.txt. EVE stays
## unconditional: the exported target links eve::eve, so it is needed by an install without tests.
##======================================================================================================================
CPMAddPackage(NAME COPACABANA GITHUB_REPOSITORY jfalcou/copacabana GIT_TAG d055131cbcc563e502321991b590d6682c6a8b3c)

CPMDeclarePackage(
  TTS
  NAME TTS
  GITHUB_REPOSITORY jfalcou/tts
  GIT_TAG e6b227c61634e4ec56b3b7ffd4a224a84f3f5c14
  SYSTEM YES
  OPTIONS "TTS_BUILD_TEST OFF" "TTS_BUILD_DOCUMENTATION OFF" "TTS_QUIET ON")
CPMAddPackage(
  NAME EVE
  GITHUB_REPOSITORY jfalcou/eve
  GIT_TAG 1d4b1906c5192313ac5aadfdd381aa5d2eded3d7
  SYSTEM YES
  OPTIONS "EVE_BUILD_TEST OFF" "EVE_BUILD_BENCHMARKS OFF" "EVE_BUILD_DOCUMENTATION OFF")
