//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::is_not_cinf over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::is_not_cinf(data), eve::true_(eve::as(data)));
};

TTS_CASE_WITH("Check kyosu::is_not_cinf over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  using T = kyosu::complex_t<decltype(r)>;
  TTS_EQUAL(kyosu::is_not_cinf(kyosu::complex(r, i)), eve::true_(eve::as(r)));
  auto z(kyosu::nan(eve::as<T>()));
  TTS_EQUAL(kyosu::is_not_cinf(z), eve::true_(eve::as(r)));
  auto ci(kyosu::cinf(eve::as<T>()));
  TTS_EQUAL(kyosu::is_not_cinf(ci), eve::false_(eve::as(r)));
};

TTS_CASE_WITH("Check kyosu::is_not_cinf is the complement of kyosu::is_cinf",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto q = type(r, i, j, k);
  TTS_EQUAL(kyosu::is_not_cinf(q), !kyosu::is_cinf(q));

  auto ci(kyosu::cinf(eve::as<kyosu::complex_t<T>>()));
  TTS_EQUAL(kyosu::is_not_cinf(ci), !kyosu::is_cinf(ci));
};

//======================================================================================================================
//== Tests for masked kyosu::is_not_cinf
//======================================================================================================================
TTS_CASE_WITH("Check kyosu::is_not_cinf[cond]",
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

  TTS_EQUAL(kyosu::is_not_cinf[cond](c), cond && kyosu::is_not_cinf(c));
  TTS_EQUAL(kyosu::is_not_cinf[cond](q), cond && kyosu::is_not_cinf(q));
};
