##======================================================================================================================
## Kyosu - Complex Without Complexes
## Copyright : KYOSU Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
copa_setup_test_targets()
add_custom_target("kyosu-bench")
set(root "${CMAKE_SOURCE_DIR}/test")

## The precompiled header carries kyosu.hpp, so a file that forgets to include it still builds.
if(KYOSU_USE_PCH)
  set(DOC_PCH   PCH kyosu_doc_pch)
  set(UNIT_PCH  PCH kyosu_pch)
  set(BENCH_PCH PCH kyosu_bench_pch)
else()
  set(DOC_PCH   "")
  set(UNIT_PCH  "")
  set(BENCH_PCH "")
endif()

##======================================================================================================================
## Documentation tests
##======================================================================================================================
copa_glob_unit(QUIET PATTERN "doc/*.cpp" INTERFACE kyosu_docs ${DOC_PCH})

##======================================================================================================================
## Unit tests
##======================================================================================================================
copa_glob_unit(QUIET PATTERN "unit/*.cpp" INTERFACE kyosu_test ${UNIT_PCH})

##======================================================================================================================
## Performance tests
##======================================================================================================================
copa_glob_unit( PATTERN "benchmarks/*.cpp"
                DESTINATION benchmarks
                RELATIVE  ${root}
                INTERFACE kyosu_bench
                ${BENCH_PCH}
                TARGET kyosu-bench
              )
