//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH ( "Check behavior of from_polar on wide"
              , kyosu::real_types
              , tts::generate( tts::randoms(-1.0, +1.0)
                             , tts::randoms(-1.0, +1.0)
                             )
              )
  <typename T>(T const& a0, T const& a1)
{
  {
    auto  c = kyosu::to_complex(a0, a1);
    auto [r1, t1] = kyosu::to_polar(c);
    auto c1 = kyosu::from_polar(r1, t1);
    TTS_RELATIVE_EQUAL(c, c1, 1.0e-5);
  }
  {
    auto [r1, t1] = kyosu::to_polar(a0);
    auto c1 = kyosu::from_polar(r1, t1);
    TTS_RELATIVE_EQUAL(kyosu::to_complex(a0), c1, 1.0e-5);
  }


};
