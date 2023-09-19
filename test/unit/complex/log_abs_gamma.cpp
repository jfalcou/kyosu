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

TTS_CASE_TPL( "Check log_abs_gamma", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using z_t = kyosu::as_complex_t<T>;
  auto tcx = [](auto r,  auto i){return kyosu::to_complex(T(r), T(i)); };
  T inf(eve::inf(eve::as<T>()));
  z_t one = tcx(1, 0);
  z_t zer = tcx(0, 0);
  z_t two = tcx(2, 0);
  z_t three = tcx(3, 0);
  TTS_IEEE_EQUAL( kyosu::log_abs_gamma(zer), inf );
  TTS_EQUAL( kyosu::log_abs_gamma(one), T(0));
  TTS_EQUAL( kyosu::log_abs_gamma(two), T(0));
  TTS_ULP_EQUAL( kyosu::log_abs_gamma(three), eve::log(T(2)), 2.0);
  TTS_ULP_EQUAL( kyosu::log_abs_gamma(tcx(-3.5, 0)), kyosu::log_abs_gamma(T(-3.5)), 2.0);
  TTS_ULP_EQUAL( kyosu::log_abs_gamma(tcx(1, 1))   ,   eve::log(kyosu::abs(tcx(0.49801566811835585, 0.1549498283018106))), 2.0);
};
