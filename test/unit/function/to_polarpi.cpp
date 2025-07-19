//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH ( "Check behavior of to_polarpi on wide"
              , kyosu::real_types
              , tts::generate( tts::randoms(-1.0, +1.0)
                             , tts::randoms(-1.0, +1.0)
                             )
              )
  <typename T>(T const& a0, T const& a1)
{
  {
    auto  c = kyosu::complex(a0, a1);
    auto [r1, t1] = kyosu::to_polarpi(c);
    auto c1 = kyosu::from_polarpi(r1, t1);
    TTS_RELATIVE_EQUAL(c, c1, tts::prec<T>());
  }
  {
    auto [r1, t1] = kyosu::to_polarpi(a0);
    auto c1 = kyosu::from_polarpi(r1, t1);
    TTS_RELATIVE_EQUAL(kyosu::complex(a0), c1, tts::prec<T>());
  }


};
