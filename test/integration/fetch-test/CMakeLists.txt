##======================================================================================================================
## Kyosu - Complex Without Complexes
## Copyright : KYOSU Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(kyosu-fetch-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing FetchContent for branch ${GIT_BRANCH}")

include(FetchContent)

# Retrieve kyosu from relative git directory
FetchContent_Declare(kyosu
  GIT_REPOSITORY "https://github.com/jfalcou/kyosu.git"
  GIT_TAG ${GIT_BRANCH}
)
FetchContent_Declare(eve
  GIT_REPOSITORY "https://github.com/jfalcou/eve.git"
  GIT_TAG main
)

## FetchContent has no per-package OPTIONS: what the dependencies read is pinned here.
set(KYOSU_BUILD_TEST        OFF CACHE BOOL "" FORCE)
set(EVE_BUILD_TEST          OFF CACHE BOOL "" FORCE)
set(EVE_BUILD_BENCHMARKS    OFF CACHE BOOL "" FORCE)
set(EVE_BUILD_DOCUMENTATION OFF CACHE BOOL "" FORCE)

# make available
FetchContent_MakeAvailable(kyosu)
FetchContent_MakeAvailable(eve)

add_executable(test_kyosu ../main.cpp)
target_link_libraries(test_kyosu PUBLIC kyosu::kyosu eve::eve)
add_test(NAME test_kyosu COMMAND test_kyosu)
