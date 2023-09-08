//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH ( "Check behavior of to_semipolar on wide"
              , kyosu::scalar_real_types
              , tts::generate( tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  {
    auto  q = kyosu::to_quaternion(a0, a1, a2, a3);
    auto [r1, t1, r2, t2] = kyosu::to_semipolar(q);
    auto q1 = kyosu::from_semipolar(r1, t1, r2, t2);
    TTS_RELATIVE_EQUAL(q, q1, 1.0e-5);
  }
  {
    auto  c = kyosu::to_complex(a0, a1);
    auto [r1, t1, r2, t2] = kyosu::to_semipolar(c);
    auto c1 = kyosu::from_semipolar(r1, t1, r2, t2);
    TTS_RELATIVE_EQUAL(kyosu::to_quaternion(c), c1, 1.0e-5);
  }

  {
    auto [r1, t1, r2, t2] = kyosu::to_semipolar(a0);
    auto q1 = kyosu::from_semipolar(r1, t1, r2, t2);
    TTS_RELATIVE_EQUAL(kyosu::to_quaternion(a0), q1, 1.0e-5);
  }


};
