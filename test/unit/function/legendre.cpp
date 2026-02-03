//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <eve/module/polynomial/regular/polynomial.hpp>

#include <kyosu/kyosu.hpp>
#include <test.hpp>

//==================================================================================================
//== legendre tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of legendre on wide", kyosu::real_types, tts::between(-1.0, 1.0))
<typename T>(T const& a0)
{
  if constexpr (sizeof(eve::element_type_t<T>) == 8)
  {
    for (unsigned int n = 0; n < 6; ++n)
    {
      TTS_ULP_EQUAL(eve::legendre(n, a0), kyosu::real(kyosu::legendre(T(n), a0)), 2000);
    }
  }
};

TTS_CASE_WITH("Check behavior of successor(legendre)", kyosu::real_types, tts::between(-1.0, 1.0))
<typename T>(T const& a0)
{
  auto pr = tts::prec<T>(1.0e-3, 1.0e-7);
  auto t3 = kyosu::legendre(3.0, a0);
  auto t4 = kyosu::legendre(4.0, a0);
  auto t5 = kyosu::legendre(5.0, a0);
  TTS_RELATIVE_EQUAL(kyosu::legendre[eve::successor](4.0, a0, t4, t3), t5, pr);
};
