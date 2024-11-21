//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>


TTS_CASE_WITH ( "Check behavior of align on wide"
              , kyosu::scalar_real_types
              , tts::generate( tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const&  a3)
{
  using kyosu::quaternion;
  using kyosu::sign;
  auto norm = [](auto &v){
    auto n = eve::hypot(v[0], v[1], v[2]);
    for(int i=0; i <= 2; ++i) v[i]/= n;
  };
  std::array<T, 3> v0{a0, a1, a2};
  std::array<T, 3> v1{a3, a1, -a2};

  auto q =  kyosu::align(std::span(v0), std::span(v1));
   norm(v0);
   norm(v1);
   auto qv0 = kyosu::rotate_vec(q, std::span(v0));
  TTS_RELATIVE_EQUAL(qv0[0], v1[0], 1.0e-4);
  TTS_RELATIVE_EQUAL(qv0[1], v1[1], 1.0e-4);
  TTS_RELATIVE_EQUAL(qv0[2], v1[2], 1.0e-4);
};
