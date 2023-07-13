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
option( KYOSU_BUILD_TEST "Build tests for KYOSU" ON )

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
  endif()
  message(STATUS "[${PROJECT_NAME}] - Unit tests        : ${KYOSU_BUILD_TEST} (via KYOSU_BUILD_TEST)")
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
copa_setup_doxygen(QUIET DESTINATION "${PROJECT_BINARY_DIR}/doc")

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(KYOSU_BUILD_TEST)
  enable_testing()
  add_custom_target(kyosu-unit    )
  add_dependencies(kyosu-unit unit)
#  add_subdirectory(test)
endif()
