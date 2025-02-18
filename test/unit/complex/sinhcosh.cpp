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


TTS_CASE_WITH( "Check behavior of sinhcosh on scalar"
        , tts::bunch<kyosu::scalar_real_types>
        , tts::generate( tts::randoms(-10, 10), tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using kc_t = kyosu::complex_t<e_t>;
  for(size_t i = 0; i < a0.size(); ++i)
  {
    auto e = kc_t(a0[i], a1[i]);
    auto [s, c] = kyosu::sinhcosh(e);
    TTS_RELATIVE_EQUAL(c,  kyosu::cosh(e), tts::prec<T>());
    TTS_RELATIVE_EQUAL(s,  kyosu::sinh(e), tts::prec<T>());
  }
};

TTS_CASE_WITH( "Check behavior of sinhcosh on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = T;
  using ke_t = kyosu::complex_t<e_t>;
  auto e = ke_t(a0, a1);
  auto [s, c] = kyosu::sinhcosh(e);
  TTS_RELATIVE_EQUAL(c,  kyosu::cosh(e), tts::prec<T>());
  TTS_RELATIVE_EQUAL(s,  kyosu::sinh(e), tts::prec<T>());
};
