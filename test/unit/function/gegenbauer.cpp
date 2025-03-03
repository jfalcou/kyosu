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
//== gegenbauer tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of gegenbauer on wide",
              kyosu::real_types,
              tts::generate(tts::between(-1.0, 1.0))
             )
  <typename T>(T const& a0)
{
  for( unsigned int n = 0; n < 6; ++n )
  {
    TTS_ULP_EQUAL(eve::gegenbauer(n, T(2.0), a0), kyosu::real(kyosu::gegenbauer(T(n), T(2.0), a0)), 4000);
  }
};
