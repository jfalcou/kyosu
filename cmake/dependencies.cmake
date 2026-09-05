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
##======================================================================================================================
CPMAddPackage ( NAME COPACABANA GITHUB_REPOSITORY jfalcou/copacabana  GIT_TAG v7)
CPMAddPackage ( NAME TTS   GITHUB_REPOSITORY jfalcou/tts
                GIT_TAG main
                OPTIONS "TTS_BUILD_TEST OFF"
                        "TTS_BUILD_DOCUMENTATION OFF"
                        "TTS_QUIET ON"
              )
CPMAddPackage ( NAME EVE   GITHUB_REPOSITORY jfalcou/eve
                GIT_TAG feat/abi-detection
                OPTIONS "EVE_BUILD_TEST OFF"
                        "EVE_BUILD_BENCHMARKS OFF"
                        "EVE_BUILD_DOCUMENTATION OFF"
              )
