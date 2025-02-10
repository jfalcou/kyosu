//      using r_t = eve::element_type_t<as_real_type_t<Z>>;
//      using r_t = eve::element_type_t<as_real_type_t<Z>>;
//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/functions/is_flint.hpp>
#include <kyosu/constants/cinf.hpp>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  confluent hypergeometric limit function 0F1({}; {b}; z)
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  template<typename Z,
           kumi::sized_product_type<0> T1,
           kumi::sized_product_type<0> T2>
  KYOSU_FORCEINLINE  auto
  hyperg(Z z, T1, T2)
  {
    return kyosu::exp(z);
  }

}
