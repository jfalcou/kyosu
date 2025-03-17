//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/functions/to_complex.hpp>
namespace kyosu
{
  template<typename T> struct complexify
  {
    using type = T;
  };

  template<concepts::real T> struct complexify<T>
  {
    using type = decltype(kyosu::complex(T()));
  };

  template < typename T> using complexify_t =  typename complexify<T>::type;
}
