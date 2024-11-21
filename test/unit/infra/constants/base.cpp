//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_TPL( "Generate basic constants on real types", kyosu::real_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(kyosu::i(kyosu::as<T>{}) , (kyosu::complex(T{0},T{ 1})));
  TTS_EQUAL(kyosu::mi(kyosu::as<T>{}), (kyosu::complex(T{0},T{-1})));
  TTS_EQUAL(kyosu::j(kyosu::as<T>{}) , (kyosu::quaternion(T{0},T{0},T{1},T{0})));
  TTS_EQUAL(kyosu::k(kyosu::as<T>{}) , (kyosu::quaternion(T{0},T{0},T{0},T{1})));

  auto ci = kyosu::cinf(kyosu::as<T>{});
  TTS_EXPECT( eve::all(eve::is_nan(kyosu::real(ci)))      );
  TTS_EXPECT( eve::all(eve::is_infinite(kyosu::imag(ci))) );
};

TTS_CASE_TPL( "Generate basic constants on complex", kyosu::real_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(kyosu::i (kyosu::as<kyosu::complex_t<T>>{}), (kyosu::complex(T{0},T{ 1})));
  TTS_EQUAL(kyosu::mi(kyosu::as<kyosu::complex_t<T>>{}), (kyosu::complex(T{0},T{-1})));
  TTS_EQUAL(kyosu::j (kyosu::as<kyosu::complex_t<T>>{}), (kyosu::quaternion(T{0},T{0},T{1},T{0})));
  TTS_EQUAL(kyosu::k (kyosu::as<kyosu::complex_t<T>>{}), (kyosu::quaternion(T{0},T{0},T{0},T{1})));

  auto ci = kyosu::cinf(kyosu::as<kyosu::complex_t<T>>{});
  TTS_EXPECT( eve::all(eve::is_nan(kyosu::real(ci)))      );
  TTS_EXPECT( eve::all(eve::is_infinite(kyosu::imag(ci))) );
};

TTS_CASE_TPL( "Generate basic constants on quaternion", kyosu::real_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(kyosu::i (kyosu::as<kyosu::quaternion_t<T>>{}), (kyosu::quaternion(T{0},T{ 1})));
  TTS_EQUAL(kyosu::mi(kyosu::as<kyosu::quaternion_t<T>>{}), (kyosu::quaternion(T{0},T{-1})));
  TTS_EQUAL(kyosu::j (kyosu::as<kyosu::quaternion_t<T>>{}), (kyosu::quaternion(T{0},T{0},T{1},T{0})));
  TTS_EQUAL(kyosu::k (kyosu::as<kyosu::quaternion_t<T>>{}), (kyosu::quaternion(T{0},T{0},T{0},T{1})));

  auto ci = kyosu::cinf(kyosu::as<kyosu::quaternion_t<T>>{});
  TTS_EXPECT( eve::all(eve::is_nan(kyosu::real(ci)))      );
  TTS_EXPECT( eve::all(eve::is_infinite(kyosu::imag(ci))) );
};

TTS_CASE_TPL( "Generate basic constants on octonion", kyosu::real_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(kyosu::i (kyosu::as<kyosu::octonion_t<T>>{}), (kyosu::octonion_t<T>(T{0},T{ 1})));
  TTS_EQUAL(kyosu::mi(kyosu::as<kyosu::octonion_t<T>>{}), (kyosu::octonion_t<T>(T{0},T{-1})));
  TTS_EQUAL(kyosu::j (kyosu::as<kyosu::octonion_t<T>>{}), (kyosu::octonion_t<T>(T{0},T{0},T{1},T{0})));
  TTS_EQUAL(kyosu::k (kyosu::as<kyosu::octonion_t<T>>{}), (kyosu::octonion_t<T>(T{0},T{0},T{0},T{1})));

  auto ci = kyosu::cinf(kyosu::as<kyosu::octonion_t<T>>{});
  TTS_EXPECT( eve::all(eve::is_nan(kyosu::real(ci)))      );
  TTS_EXPECT( eve::all(eve::is_infinite(kyosu::imag(ci))) );
};
