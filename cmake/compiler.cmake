##======================================================================================================================
##  Kyosu - Complex Without Complexes
##  Copyright : KYOSU Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================


##======================================================================================================================
## Compiler options for Doc Tests
##======================================================================================================================
add_library(kyosu_docs INTERFACE)

target_compile_features ( kyosu_docs INTERFACE  cxx_std_20 )

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    target_compile_options( kyosu_docs INTERFACE /W3 /EHsc )
  else()
    target_compile_options( kyosu_docs INTERFACE -Werror -Wall -Wextra -Wunused-variable)
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options( kyosu_docs INTERFACE /W3 /EHsc /Zc:preprocessor)
else()
  target_compile_options( kyosu_docs INTERFACE -Werror -Wall -Wextra -Wunused-variable)
endif()

target_include_directories( kyosu_docs INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/include
                          )

target_link_libraries(kyosu_docs INTERFACE eve::eve)

##======================================================================================================================
## Compiler options for Unit Tests
##======================================================================================================================
add_library(kyosu_test INTERFACE)

target_link_libraries(kyosu_test INTERFACE kyosu_docs tts::tts)
