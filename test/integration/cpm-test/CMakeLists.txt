##======================================================================================================================
## Kyosu - Complex Without Complexes
## Copyright : KYOSU Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.18)
project(kyosu-cpm-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing CPM for branch ${GIT_BRANCH}")

# Setup CPM
include(cpm.cmake)

# Add dependencies
CPMAddPackage ( NAME kyosu
                GIT_REPOSITORY "https://github.com/jfalcou/kyosu.git"
                GIT_TAG "${GIT_BRANCH}"
                OPTIONS "KYOSU_BUILD_TEST OFF"
              )

# Use kyosu
add_executable(test_kyosu ../main.cpp)
target_link_libraries(test_kyosu PUBLIC kyosu::kyosu eve::eve)
add_test(NAME test_kyosu COMMAND test_kyosu)
