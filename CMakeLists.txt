##======================================================================================================================
##  Kyosu - Complex Math Made Easy
##  Copyright : KYOSU Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(kyosu LANGUAGES CXX)
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)

##======================================================================================================================
option( KYOSU_BUILD_TEST          "Build tests for KYOSU"   ON  )
option( KYOSU_BUILD_DOCUMENTATION "Build Doxygen for KYOSU" OFF )

##======================================================================================================================
## Project setup via copacabana
##======================================================================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${COPACABANA_SOURCE_DIR}/copacabana/cmake)
include(${COPACABANA_SOURCE_DIR}/copacabana/cmake/copacabana.cmake)
copa_project_version(MAJOR 2 MINOR 3 PATCH 0)

##======================================================================================================================
## Summary Display
##======================================================================================================================
if(NOT KYOSU_QUIET)
  if(CMAKE_BUILD_TYPE)
    message(STATUS "[${PROJECT_NAME}] - Building in ${CMAKE_BUILD_TYPE} mode")
  set(QUIET_OPTION "")
  endif()
  message(STATUS "[${PROJECT_NAME}] - Unit tests : ${KYOSU_BUILD_TEST} (via KYOSU_BUILD_TEST)")
  message(STATUS "[${PROJECT_NAME}] - Doxygen    : ${KYOSU_BUILD_DOCUMENTATION} (via KYOSU_BUILD_DOCUMENTATION)")
  set(QUIET_OPTION "QUIET")
endif()

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
  copa_setup_doxygen(${QUIET_OPTION} DESTINATION "${PROJECT_BINARY_DIR}/doc")
endif()

##======================================================================================================================
## Setup PCH
##======================================================================================================================
copa_setup_pch( TARGET kyosu      INTERFACES  kyosu_test HEADERS include/kyosu/kyosu.hpp)
copa_setup_pch( TARGET kyosu_doc  INTERFACES  kyosu_docs HEADERS include/kyosu/kyosu.hpp)

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(KYOSU_BUILD_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
