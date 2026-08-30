//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::is_pure over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::is_pure(data), eve::is_eqz(data));
};

TTS_CASE_WITH("Check kyosu::is_pure over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  TTS_EQUAL(kyosu::is_pure(kyosu::complex(r, i)), eve::is_eqz(r));
  TTS_EQUAL(kyosu::is_pure(kyosu::complex(eve::zero(eve::as(r)), i)), eve::true_(eve::as(r)));
};

TTS_CASE_WITH("Check kyosu::is_pure over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::is_pure(type(r, i, j, k)), eve::is_eqz(r));
  TTS_EQUAL(kyosu::is_pure(type(eve::zero(eve::as(r)), i, j, k)), eve::true_(eve::as(r)));
};

TTS_CASE_WITH("Check kyosu::is_pure over octonion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
<typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  TTS_EQUAL(kyosu::is_pure(type(r, i, j, k, l, li, lj, lk)), eve::is_eqz(r));
  TTS_EQUAL(kyosu::is_pure(type(eve::zero(eve::as(r)), i, j, k, l, li, lj, lk)), eve::true_(eve::as(r)));
};

//======================================================================================================================
//== Tests for masked kyosu::is_pure
//======================================================================================================================
TTS_CASE_WITH("Check kyosu::is_pure[cond]",
              kyosu::simd_real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
<typename T>(T a0, T a1, T a2, T a3)
{
  auto c = kyosu::complex(a0, a1);
  auto q = kyosu::quaternion_t<T>(a0, a1, a2, a3);
  auto cond = eve::is_even(eve::iota(eve::as<T>()));

  TTS_EQUAL(kyosu::is_pure[cond](c), cond && kyosu::is_pure(c));
  TTS_EQUAL(kyosu::is_pure[cond](q), cond && kyosu::is_pure(q));
};
