//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>


TTS_CASE_WITH ( "Check behavior of slerp on"
              , kyosu::real_types
              , tts::generate( tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             , tts::randoms(0.25, +0.75)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3
              , T const& a4, T const& a5, T const& a6, T const& a7)
{
  using e_t =  eve::element_type_t<T>;
  using q_t =  kyosu::as_quaternion_t<T>;
  if constexpr(sizeof(e_t) == 8)
  {
    auto z1 = kyosu::sign(q_t(a0, a1, a2, a3));
    auto z2 = kyosu::sign(q_t(a4, a5, a6, a7));
    auto dz1z2 = kyosu::dot(z1, z2);
    z2 = kyosu::if_else(eve::is_gez(dz1z2), z2, -z2);
    auto r1 = kyosu::slerp(z1, z2, e_t(0.0));
    auto t1 = kyosu::conj(z1)*z2;
    auto t2 = kyosu::pow(t1, e_t(0.0));
    auto t3 = z1*t2;
    TTS_RELATIVE_EQUAL(r1, t3, 0.0001);
  }
};
