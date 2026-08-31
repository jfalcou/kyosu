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
option( KYOSU_USE_PCH             "Build tests with precompiled headers"                            ON  )
option( KYOSU_BUILD_TEST          "Build tests for KYOSU"   ON  )
option( KYOSU_BUILD_DOCUMENTATION "Build Doxygen for KYOSU" OFF )
option( KYOSU_ENABLE_SANITIZERS   "Build tests with AddressSanitizer + UndefinedBehaviorSanitizer" OFF )
option( KYOSU_ENABLE_COVERAGE     "Build tests with code coverage instrumentation"                 OFF )
option( KYOSU_BUILD_DEMOS         "Build the interactive demos"                                    OFF )

##======================================================================================================================
## Project setup via copacabana
##======================================================================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${COPACABANA_SOURCE_DIR}/copacabana/cmake)
include(${COPACABANA_SOURCE_DIR}/copacabana/cmake/copacabana.cmake)
copa_project_version(MAJOR 0 MINOR 1 PATCH 0)

##======================================================================================================================
## Summary Display
##======================================================================================================================
if(NOT KYOSU_QUIET)
  if(CMAKE_BUILD_TYPE)
    message(STATUS "[${PROJECT_NAME}] - Building in ${CMAKE_BUILD_TYPE} mode")
  endif()
  message(STATUS "[${PROJECT_NAME}] - Use PCH    : ${KYOSU_USE_PCH} (via KYOSU_USE_PCH)")
  message(STATUS "[${PROJECT_NAME}] - Unit tests : ${KYOSU_BUILD_TEST} (via KYOSU_BUILD_TEST)")
  message(STATUS "[${PROJECT_NAME}] - Doxygen    : ${KYOSU_BUILD_DOCUMENTATION} (via KYOSU_BUILD_DOCUMENTATION)")
  message(STATUS "[${PROJECT_NAME}] - Sanitizers : ${KYOSU_ENABLE_SANITIZERS} (via KYOSU_ENABLE_SANITIZERS)")
  message(STATUS "[${PROJECT_NAME}] - Coverage   : ${KYOSU_ENABLE_COVERAGE} (via KYOSU_ENABLE_COVERAGE)")
  message(STATUS "[${PROJECT_NAME}] - Demos      : ${KYOSU_BUILD_DEMOS} (via KYOSU_BUILD_DEMOS)")
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
  ## Doxygen never fetches anything itself, so eve's tagfile has to be on disk before the target
  ## runs. The Doxyfile reaches it through $(DOXYGEN_OUPUT), the only handle copacabana exports
  ## that points into the build tree. Without it the eve:: references stay unresolved.
  file( DOWNLOAD "https://jfalcou.github.io/eve/eve.tag" "${PROJECT_BINARY_DIR}/eve.tag"
        STATUS EVE_TAG_STATUS
      )
  list(GET EVE_TAG_STATUS 0 EVE_TAG_CODE)
  if(NOT EVE_TAG_CODE EQUAL 0)
    message(WARNING "[${PROJECT_NAME}] - eve.tag could not be fetched (${EVE_TAG_STATUS}), the eve:: links will be dead")
  endif()

  copa_setup_doxygen(${QUIET_OPTION} DESTINATION "${PROJECT_BINARY_DIR}/doc")

  ## Reading eve.tag is what makes the eve:: references resolve, and it also hands doxygen every symbol eve documents,
  ## which then fills kyosu's search box. Doxygen has no setting for that, so the index is trimmed afterwards.
  ## Belongs in copacabana once it hosts the tagfile machinery - jfalcou/copacabana#28.
  add_custom_command( TARGET kyosu-doxygen POST_BUILD
                      COMMAND ${CMAKE_COMMAND} -E env python3
                              "${PROJECT_SOURCE_DIR}/doc/strip_external_search.py"
                              "${PROJECT_BINARY_DIR}/doc/search"
                      COMMENT "[${PROJECT_NAME}] - Dropping the external symbols from the search index"
                      VERBATIM
                    )
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
