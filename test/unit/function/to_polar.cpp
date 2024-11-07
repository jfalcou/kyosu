//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH ( "Check behavior of to_polar on wide"
              , kyosu::real_types
              , tts::generate( tts::randoms(-1.0, +1.0)
                             , tts::randoms(-1.0, +1.0)
                             , tts::randoms(-1.0, +1.0)
                             , tts::randoms(-1.0, +1.0)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  {
    auto  q = kyosu::quaternion(a0, a1, a2, a3);
    auto [r, t, iz] = kyosu::to_polar(q);
    auto q1 = kyosu::from_polar(r, t, iz);
    TTS_RELATIVE_EQUAL(q, q1, 1.0e-5);
  }
  {
    auto  c = kyosu::complex(a0, a1);
    auto [r1, t1] = kyosu::to_polar(c);
    auto c1 = kyosu::from_polar(r1, t1);
    TTS_RELATIVE_EQUAL(c, c1, 1.0e-5);
  }
  {
    auto [r1, t1] = kyosu::to_polar(a0);
    auto c1 = kyosu::from_polar(r1, t1);
    TTS_RELATIVE_EQUAL(kyosu::complex(a0), c1, 1.0e-5);
  }


};
