//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::is_unitary over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  auto o = eve::one(eve::as(data));
  TTS_EQUAL(kyosu::is_unitary(data), data == o);
};

TTS_CASE_WITH ( "Check kyosu::is_unitary over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10))
              )
(auto r, auto i)
{
  auto c = kyosu::to_complex(r,i);
  c /= kyosu::abs(c);
  auto o = eve::one(eve::as(kyosu::abs(c)));
  TTS_EQUAL(kyosu::is_unitary(c), eve::almost(eve::is_equal)(kyosu::abs(c), o));
};

TTS_CASE_WITH ( "Check kyosu::is_unitary over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::as_quaternion_t<T>;
  auto z(type(r,i,j,k));
  z /= kyosu::abs(z);
  auto o = eve::one(eve::as(kyosu::abs(z)));
  TTS_EQUAL(kyosu::is_unitary(z), eve::almost(eve::is_equal)(kyosu::abs(z), o));
};

TTS_CASE_WITH ( "Check kyosu::is_unitary over octonion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::as_octonion_t<T>;
  auto z(type(r,i,j,k,l,li,lj,lk));
  z /= kyosu::abs(z);
  auto o = eve::one(eve::as(kyosu::abs(z)));
  TTS_EQUAL(kyosu::is_unitary(z), eve::almost(eve::is_equal)(kyosu::abs(z), o));
};
