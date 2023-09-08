//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>


TTS_CASE_WITH ( "Check behavior of rotate_vec on wide"
              , kyosu::real_types
              , tts::generate( tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2)
{
  {
    auto z = kyosu::from_euler(a0, a1, a2, kyosu::_Z, kyosu::_X, kyosu::_Z, kyosu::Extrinsic);
    auto [t1, t2, t3] = kyosu::to_euler(z, kyosu::_Z, kyosu::_X, kyosu::_Z, kyosu::Extrinsic);
    TTS_RELATIVE_EQUAL(t1, a0, 1.0e-4);
    TTS_RELATIVE_EQUAL(t2, a1, 1.0e-4);
    TTS_RELATIVE_EQUAL(t3, a2, 1.0e-4);
  }
  {
    auto z = kyosu::from_euler(a0, a1, a2, kyosu::_Z, kyosu::_X, kyosu::_Z, kyosu::Intrinsic);
    auto [t1, t2, t3] = kyosu::to_euler(z, kyosu::_Z, kyosu::_X, kyosu::_Z, kyosu::Intrinsic);
    TTS_RELATIVE_EQUAL(t1, a0, 1.0e-4);
    TTS_RELATIVE_EQUAL(t2, a1, 1.0e-4);
    TTS_RELATIVE_EQUAL(t3, a2, 1.0e-4);
  }

};
