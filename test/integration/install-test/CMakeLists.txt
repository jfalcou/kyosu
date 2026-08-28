##======================================================================================================================
## Kyosu - Complex Without Complexes
## Copyright : KYOSU Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(kyosu-install-test LANGUAGES CXX)
enable_testing()

## Fake install via FetchContent

include(FetchContent)
FetchContent_Declare(eve
  GIT_REPOSITORY "https://github.com/jfalcou/eve.git"
  GIT_TAG main
)

## Nothing else populates eve here, so its options would stay at their defaults.
set(EVE_BUILD_TEST          OFF CACHE BOOL "" FORCE)
set(EVE_BUILD_BENCHMARKS    OFF CACHE BOOL "" FORCE)
set(EVE_BUILD_DOCUMENTATION OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(eve)

find_package(kyosu CONFIG REQUIRED)
add_executable(test_kyosu ../main.cpp)
target_link_libraries(test_kyosu PUBLIC kyosu::kyosu eve::eve)
add_test(NAME test_kyosu COMMAND test_kyosu)
