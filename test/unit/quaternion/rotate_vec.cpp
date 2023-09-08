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
                             , tts::randoms(0.25, +0.75)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  auto pr = [](auto name, auto v){std::cout << name << v[0] << ", " << v[1] << ", " << v[2] << std::endl; };
  {
    std::array<T, 3> v{a0, a1, a2};
    auto rsq3 = eve::rec(eve::sqrt_3(eve::as(a3)));
    std::array<T, 3> axis{rsq3, rsq3, rsq3};
    pr("axis = ", axis);
    auto  q = kyosu::from_angle_axis(eve::pi(eve::as(a0)), std::span<T, 3>(axis));
    auto vr = kyosu::rotate_vec(q, std::span<T, 3>(v), kyosu::Normalize);
    auto vr2= kyosu::rotate_vec(q, std::span<T, 3>(vr), kyosu::Normalize);
    pr("v   = ", v);
    pr("vr  = ", vr);
    pr("vr2 = ", vr2);
    TTS_RELATIVE_EQUAL(v[0], vr2[0], 1.0e-4);
  }
};
