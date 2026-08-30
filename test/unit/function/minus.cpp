//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::minus over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::minus(data), -data);
};

TTS_CASE_WITH("Check kyosu::minus over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  TTS_EQUAL(kyosu::minus(kyosu::complex(r, i)), kyosu::complex(-r, -i));
};

TTS_CASE_WITH("Check kyosu::minus over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::minus(type(r, i, j, k)), type(-r, -i, -j, -k));
};

//======================================================================================================================
//== Tests for masked kyosu::minus
//======================================================================================================================
TTS_CASE_WITH("Check kyosu::minus[cond]",
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

  TTS_RELATIVE_EQUAL(kyosu::minus[cond](c), kyosu::if_else(cond, kyosu::minus(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::minus[cond](q), kyosu::if_else(cond, kyosu::minus(q), q), tts::prec<T>());
};
