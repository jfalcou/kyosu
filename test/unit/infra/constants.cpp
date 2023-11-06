//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL( "Check as_real behavior on real types", kyosu::real_types)
<typename T>(tts::type<T>)
{
  T x = {};

  TTS_EQUAL(eve::half(kyosu::as_real<T>{}), T{0.5});
  TTS_EQUAL(eve::half(kyosu::as_real(x)), T{0.5});
};

TTS_CASE_TPL( "Check as_real behavior on non-real types", kyosu::real_types)
<typename T>(tts::type<T>)
{
  kyosu::complex_t<T>     cx = {};
  kyosu::quaternion_t<T>  qx = {};
  kyosu::octonion_t<T>    ox = {};

  TTS_EQUAL(eve::half(kyosu::as_real<kyosu::complex_t<T>>{}), T{0.5});
  TTS_EQUAL(eve::half(kyosu::as_real<kyosu::quaternion_t<T>>{}), T{0.5});
  TTS_EQUAL(eve::half(kyosu::as_real<kyosu::octonion_t<T>>{}), T{0.5});

  TTS_EQUAL(eve::half(kyosu::as_real(cx)), T{0.5});
  TTS_EQUAL(eve::half(kyosu::as_real(qx)), T{0.5});
  TTS_EQUAL(eve::half(kyosu::as_real(ox)), T{0.5});
};

TTS_CASE_TPL( "Check as behavior on non-real types", kyosu::real_types)
<typename T>(tts::type<T>)
{
  kyosu::complex_t<T>     cx = {};
  kyosu::quaternion_t<T>  qx = {};
  kyosu::octonion_t<T>    ox = {};

  TTS_EQUAL(eve::half(kyosu::as<kyosu::complex_t<T>>{})   , kyosu::complex_t<T>(0.5));
  TTS_EQUAL(eve::half(kyosu::as<kyosu::quaternion_t<T>>{}), kyosu::quaternion_t<T>{0.5});
  TTS_EQUAL(eve::half(kyosu::as<kyosu::octonion_t<T>>{})  , kyosu::octonion_t<T>{0.5});

  TTS_EQUAL(eve::half(kyosu::as(cx)),kyosu::complex_t<T>(0.5));
  TTS_EQUAL(eve::half(kyosu::as(qx)),kyosu::quaternion_t<T>{0.5});
  TTS_EQUAL(eve::half(kyosu::as(ox)),kyosu::octonion_t<T>{0.5});
};
