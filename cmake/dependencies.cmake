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
CPMAddPackage ( NAME COPACABANA GITHUB_REPOSITORY jfalcou/copacabana  GIT_TAG cc2bc58c53c64c7cc47b611fee219b0cefa27d43)

CPMDeclarePackage ( TTS   NAME TTS   GITHUB_REPOSITORY jfalcou/tts
                    GIT_TAG d0ee3e83481ba048dc054d5fc66158d4b980c928
                    SYSTEM YES
                    OPTIONS "TTS_BUILD_TEST OFF"
                            "TTS_BUILD_DOCUMENTATION OFF"
                            "TTS_QUIET ON"
                  )
CPMAddPackage ( NAME EVE   GITHUB_REPOSITORY jfalcou/eve
                GIT_TAG d54c6c64b0d951dfbac475896e41c2be97a5500f
                SYSTEM YES
                OPTIONS "EVE_BUILD_TEST OFF"
                        "EVE_BUILD_BENCHMARKS OFF"
                        "EVE_BUILD_DOCUMENTATION OFF"
              )
