##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(root "${CMAKE_SOURCE_DIR}/benchmarks")
set(PROJECT_TEST_TARGET "kyosu-bench")
add_custom_target(${PROJECT_TEST_TARGET})

##==================================================================================================
## GLOB and process complex bench
##==================================================================================================


copa_glob_unit( PATTERN "complex/*.cpp"
                DESTINATION benchmarks
                RELATIVE  ${root}
                INTERFACE kyosu_bench
                PCH kyosu_bench_pch
              )
