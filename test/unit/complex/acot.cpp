//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <complex>

TTS_CASE_WITH ( "Check behavior of acot on scalar"
              , tts::bunch<kyosu::scalar_real_types>
              , tts::generate( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
              )
  <typename T>(T const& a0, T const& a1 )
{
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = kyosu::to_complex(e, f);
      TTS_RELATIVE_EQUAL(kyosu::acot(z),  kyosu::atan(kyosu::rec(z)), 1.0e-50);
    }
  }
};

TTS_CASE_WITH( "Check behavior of acot on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const&  a1)
{
  auto z = kyosu::to_complex(a0, a1);
  TTS_RELATIVE_EQUAL(kyosu::acot(z), kyosu::atan(kyosu::rec(z)), 1.0e-5);
};
