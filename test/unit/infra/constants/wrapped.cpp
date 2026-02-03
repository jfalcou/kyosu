//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL("Generate half", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using kyosu::complex_t;
  using kyosu::octonion_t;
  using kyosu::quaternion_t;

  TTS_EQUAL(kyosu::half(kyosu::as<T>{}), T{0.5});
  TTS_EQUAL(kyosu::half(kyosu::as<complex_t<T>>{}), complex_t<T>{0.5});
  TTS_EQUAL(kyosu::half(kyosu::as<quaternion_t<T>>{}), quaternion_t<T>{0.5});
  TTS_EQUAL(kyosu::half(kyosu::as<octonion_t<T>>{}), octonion_t<T>{0.5});
};

TTS_CASE_TPL("Generate pi", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using kyosu::complex_t;
  using kyosu::octonion_t;
  using kyosu::quaternion_t;

  TTS_EQUAL(kyosu::pi(kyosu::as<T>{}), eve::pi(eve::as<T>{}));
  TTS_EQUAL(kyosu::pi(kyosu::as<complex_t<T>>{}), complex_t<T>{eve::pi(eve::as<T>{})});
  TTS_EQUAL(kyosu::pi(kyosu::as<quaternion_t<T>>{}), quaternion_t<T>{eve::pi(eve::as<T>{})});
  TTS_EQUAL(kyosu::pi(kyosu::as<octonion_t<T>>{}), octonion_t<T>{eve::pi(eve::as<T>{})});
};
