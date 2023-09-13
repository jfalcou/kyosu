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
  using e_t = T;
  T nan(eve::nan(eve::as<T>()));
  z_t one(e_t(1));
  z_t zer{};
  z_t two(e_t(2));
  z_t three(e_t(3));
  TTS_IEEE_EQUAL( kyosu::log_gamma(zer), kyosu::to_complex(nan, nan) );
  TTS_EQUAL( kyosu::log_gamma(one), zer );
  TTS_EQUAL( kyosu::log_gamma(two), zer);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(three), kyosu::log(two), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(-3.5, 0)), z_t(-1.309006684993043, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(1, 1))   , z_t( -0.650923199301856, -0.301640320467534), 1.0e-5);

  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t( 3.5, 0)), z_t(1.2009736023470742, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(-3.5, 0)), z_t(-1.309006684993042, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(3.75, 0)), z_t(1.48681557859341705, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(-3.75, 0)), z_t(-1.317267942446363, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(4, 0))    , z_t(eve::log(T(6)))                , 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(1, 1))   , z_t(-0.6509231993018563, -0.301640320467533197887531), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(-1,1))   , z_t(-0.9974967895818289, +2.054554169724811730959450), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(1, -1))  , z_t(-0.6509231993018563, +0.301640320467533197887531), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(-1,-1))  , z_t(-0.997496789581828993, -2.054554169724811730959450), 1.0e-5);
  TTS_IEEE_EQUAL( kyosu::log_gamma(z_t(-1,0))   , z_t(eve::nan(eve::as<e_t>()), eve::inf(eve::as<e_t>())));
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(1, -2))  , z_t(-1.876078786430929341, -0.12964631630978831138370), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::log_gamma(z_t(-1,-2))  , z_t(-3.37394492320792483, -2.80759136089877543363209), 1.0e-5);
};
