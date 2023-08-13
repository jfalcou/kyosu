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

FetchContent_MakeAvailable(eve)

find_package(kyosu CONFIG REQUIRED)
add_executable(test_kyosu ../main.cpp)
target_link_libraries(test_kyosu PUBLIC kyosu::kyosu eve::eve)
add_test(NAME test_kyosu COMMAND test_kyosu)
