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
  z_t i = kyosu::to_complex(T(0), T(1));
  z_t o = kyosu::to_complex(T(1), T(0));
  z_t h = kyosu::to_complex(T(0.5), T(0));
  TTS_RELATIVE_EQUAL(kyosu::beta(i, i),      z_t(-2.376146124821733192409666, -2.63956852027813624177239618242498), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::beta(i, h),      z_t(1.0794242492709257801356755, -1.41003240566416083828875193632476), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::beta(i, T(0.5)), z_t(1.0794242492709257801356755, -1.41003240566416083828875193632476), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::beta(i, o), -i ,                                                                        1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::beta(o, T(0.5)), z_t(2)                                                               , 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::beta(i, 2*i),    z_t(-2.891319789417896828442673, -1.04053537453220827379062834820451), 1.0e-5);
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
  auto a = kyosu::to_complex(a0, a1);
  auto b = kyosu::to_complex(a2, a3);

  auto mybeta = [](auto a,  auto b){return kyosu::tgamma(a)*kyosu::tgamma(b)/kyosu::tgamma(a+b); };
  TTS_IEEE_EQUAL(kyosu::beta(a, b), mybeta(a, b));
};
