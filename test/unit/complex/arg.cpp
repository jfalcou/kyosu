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


TTS_CASE_WITH( "Check behavior of arg on scalar"
        , tts::bunch<kyosu::scalar_real_types>
        , tts::generate( tts::randoms(-10, 10), tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  for(size_t i = 0; i < a0.size(); ++i)
  {
    auto e = a0[i];
    auto f = a1[i];

    TTS_RELATIVE_EQUAL(kyosu::arg(kyosu::complex(e, f)),  eve::atan2(f, e), 1.0e-6);
  }
};

TTS_CASE_WITH( "Check behavior of arg on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::between(-10, 10)
                            , tts::between(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  TTS_RELATIVE_EQUAL(kyosu::arg(kyosu::complex(a0,a1)), eve::atan2(a1, a0), 1.0e-6);
};
