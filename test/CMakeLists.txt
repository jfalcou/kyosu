##======================================================================================================================
## Kyosu - Complex Math Made Easy
## Copyright : TTS Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
copa_setup_test_targets()
set(root "${CMAKE_SOURCE_DIR}/test")

##======================================================================================================================
## Complex tests
##======================================================================================================================
copa_glob_unit(PATTERN "complex/*.cpp" INTERFACE kyosu_test)
copa_glob_unit(PATTERN "quaternion/*.cpp" INTERFACE kyosu_test)
