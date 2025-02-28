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
//== tchebytchev tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of tchebytchev on wide",
              kyosu::real_types,
              tts::generate(tts::between(-1.0, 1.0))
             )
  <typename T>(T const& a0)
{
  if constexpr(sizeof(eve::element_type_t<T>) == 8)
  {
    for( unsigned int n = 0; n < 6; ++n )
    {
      TTS_ULP_EQUAL(eve::tchebytchev(n, a0), kyosu::real(kyosu::tchebytchev(T(n), a0)), 4000);
    }
  }
};
