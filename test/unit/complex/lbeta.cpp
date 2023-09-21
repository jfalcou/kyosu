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

TTS_CASE_TPL( "Check log_abs_gamma", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using z_t = kyosu::complex_t<T>;
  z_t i = kyosu::complex(T(0), T(1));
  z_t o = kyosu::complex(T(1), T(0));
  TTS_RELATIVE_EQUAL(kyosu::lbeta(i, i),      z_t(1.2673795683871619728767940, -2.30372328403975132639009246361848), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::lbeta(i, T(0.5)), z_t(0.574232387827216663459561, -0.917428922919860707555628220702128), 1.0e-5);
  TTS_ABSOLUTE_EQUAL(kyosu::lbeta(i, o), z_t(0, -eve::pio_2(eve::as<T>()))                                               , 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::lbeta(o, T(0.5)), z_t(eve::log(T(2)))                                                  , 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::lbeta(i, 2*i),    z_t(1.122607421965134893435985, -2.796141102021254706058936433559202), 1.0e-5);
};


TTS_CASE_WITH ( "Check behavior of pow on wide"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  auto a = kyosu::complex(a0, a1);
  auto b = kyosu::complex(a2, a3);

  auto mylbeta = [](auto a,  auto b){return kyosu::log(kyosu::beta(a, b)); };
  TTS_IEEE_EQUAL(kyosu::lbeta(a, b), mylbeta(a, b));
};
