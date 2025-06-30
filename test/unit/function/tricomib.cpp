//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <iomanip>
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <eve/wide.hpp>
#include <iostream>

TTS_CASE_TPL ( "Check tricomi "
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  if constexpr(sizeof(T) == 8)
  {
    auto pr = tts::prec<T>(4.0e-3, 1.0e-8);
    using r_t = kyosu::cayley_dickson<T, 2>;
    auto cinf = kyosu::cinf(eve::as<r_t>());
    r_t res[] = {r_t(-0.454219904863173, -3.141592653589793238)
    };
    r_t r(cinf);
    r = kyosu::tricomi(-2.0, 2.0, 2.0);
    TTS_RELATIVE_EQUAL(r, res[0], pr);
  }
};
