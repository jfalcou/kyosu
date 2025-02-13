//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::is_cinf over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  (auto data)
{
  TTS_EQUAL(kyosu::is_cinf(data), eve::false_(eve::as(data)));
};

TTS_CASE_WITH ( "Check kyosu::is_cinf over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
  (auto r, auto i)
{
  using T = kyosu::complex_t<decltype(r)>;
  TTS_EQUAL(kyosu::is_cinf(kyosu::complex(r,i)), eve::is_infinite(r) && eve::is_nan(i));
  auto z(kyosu::nan(eve::as<T>()));
  TTS_EQUAL(kyosu::is_cinf(z), eve::false_(eve::as(r)));
  auto zz = kyosu::complex (eve::nan(eve::as(r)), eve::inf(eve::as(r)));
  TTS_EQUAL(kyosu::is_cinf(zz), eve::true_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_cinf over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto z(kyosu::cinf(eve::as(r)));
  TTS_EQUAL(kyosu::is_cinf(type(r,i,j,k)), eve::is_nan(r) && eve::is_nan(i) && eve::is_nan(j) && eve::is_nan(k));
  TTS_EQUAL(kyosu::is_cinf(z), eve::true_(eve::as(r)));
  type zz(kyosu::nan(eve::as<type>()));
  TTS_EQUAL(kyosu::is_cinf(zz), eve::false_(eve::as(r)));
};
