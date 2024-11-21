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
  using kyosu::as;
  using z_t = kyosu::complex_t<T>;
  using e_t = T;
  auto tcx = [](auto r,  auto i){return kyosu::complex(T(r), T(i)); };
  z_t one = tcx(1, 0);
  z_t zer = tcx(0, 0);
  z_t two = tcx(2, 0);
  z_t three = tcx(3, 0);
  TTS_IEEE_EQUAL( kyosu::log_gamma(zer), kyosu::complex(eve::inf(as<T>()), eve::zero(as<T>())) );
  TTS_EQUAL( kyosu::log_gamma(one), zer );
  TTS_EQUAL( kyosu::log_gamma(two), zer);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(three), kyosu::log(two), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(-3.5, 0)), tcx(-1.309006684993043, 0), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(1, 1))   , tcx( -0.650923199301856, -0.301640320467534), tts::prec<T>());

  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx( 3.5, 0)), tcx(1.2009736023470742, 0), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(-3.5, 0)), tcx(-1.309006684993042, 0), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(3.75, 0)), tcx(1.48681557859341705, 0), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(-3.75, 0)), tcx(-1.317267942446363, 0), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(4, 0))    , tcx(eve::log(T(6)), 0)                , tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(1, 1))   , tcx(-0.6509231993018563, -0.301640320467533197887531), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(-1,1))   , tcx(-0.9974967895818289, +2.054554169724811730959450), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(1, -1))  , tcx(-0.6509231993018563, +0.301640320467533197887531), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(-1,-1))  , tcx(-0.997496789581828993, -2.054554169724811730959450), tts::prec<T>());
  TTS_IEEE_EQUAL( kyosu::log_gamma(tcx(-1,0))   , tcx(eve::nan(eve::as<e_t>()), eve::inf(eve::as<e_t>())));
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(1, -2))  , tcx(-1.876078786430929341, -0.12964631630978831138370), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(tcx(-1,-2))  , tcx(-3.37394492320792483, -2.80759136089877543363209), tts::prec<T>());
};
