##======================================================================================================================
## Kyosu - Complex Math Made Easy
## Copyright : KYOSU Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(kyosu-install-test LANGUAGES CXX)
enable_testing()

find_package(kyosu CONFIG REQUIRED)
add_executable(test_kyosu ../main.cpp)
target_link_libraries(test_kyosu PUBLIC kyosu::kyosu)
add_test(NAME test_kyosu COMMAND test_kyosu)
