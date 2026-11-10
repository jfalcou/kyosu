##======================================================================================================================
##  Kyosu - Complex Without Complexes
##  Copyright : KYOSU Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

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
CPMAddPackage(NAME COPACABANA GITHUB_REPOSITORY jfalcou/copacabana GIT_TAG 064ed5a324ac0fb2629c2a5953b83aac9f9436a5)

CPMDeclarePackage(
  TTS
  NAME TTS
  GITHUB_REPOSITORY jfalcou/tts
  GIT_TAG 4ac6e558e767c0df56f59a132873d1873d6023ba
  SYSTEM YES
  OPTIONS "TTS_BUILD_TEST OFF" "TTS_BUILD_DOCUMENTATION OFF" "TTS_QUIET ON")
CPMAddPackage(
  NAME EVE
  GITHUB_REPOSITORY jfalcou/eve
  GIT_TAG 960b6c447ea525be2382ccb5262f87edcfce4550
  SYSTEM YES
  OPTIONS "EVE_BUILD_TEST OFF" "EVE_BUILD_BENCHMARKS OFF" "EVE_BUILD_DOCUMENTATION OFF")
