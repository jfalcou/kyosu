##======================================================================================================================
## Kyosu - Complex Without Complexes
## Copyright : KYOSU Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
copa_setup_test_targets()
set(root "${CMAKE_SOURCE_DIR}/test")

##======================================================================================================================
## Documentation tests
##======================================================================================================================
copa_glob_unit(QUIET PATTERN "doc/*.cpp"    INTERFACE kyosu_docs PCH kyosu_doc_pch)

##======================================================================================================================
## Unit tests
##======================================================================================================================
copa_glob_unit(QUIET PATTERN "unit/complex/*.cpp"     INTERFACE kyosu_test PCH kyosu_pch)
copa_glob_unit(QUIET PATTERN "unit/quaternion/*.cpp"  INTERFACE kyosu_test PCH kyosu_pch)
copa_glob_unit(QUIET PATTERN "unit/function/*.cpp"    INTERFACE kyosu_test PCH kyosu_pch)
