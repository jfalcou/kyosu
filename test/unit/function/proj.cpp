//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::dec over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::proj(data), data);
  TTS_EQUAL(kyosu::proj(eve::minf(eve::as(data))), eve::inf(eve::as(data)));
};

TTS_CASE_WITH("Check kyosu::proj over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T r, T i)
{
  using eve::as;
  using type = kyosu::complex_t<T>;
  auto c = type(r, i);
  TTS_EQUAL(kyosu::proj(c), c);
  auto c1 = type(eve::minf(as(r)), i);
  auto pc1 = type(eve::inf(as(r)), eve::bit_and(eve::sign(i), eve::mzero(as(r))));
  auto c2 = type(r, eve::minf(as(i)));
  auto pc2 = type(eve::inf(as(r)), eve::bit_and(eve::sign(i), eve::mzero(as(r))));
  TTS_EQUAL(kyosu::proj(c1), pc1);
  TTS_EQUAL(kyosu::proj(c2), pc2);
};

TTS_CASE_WITH("Check kyosu::proj over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r, T i, T j, T k)
{
  using eve::as;
  auto g = [](auto x) { return eve::bit_and(eve::sign(x), eve::mzero(as(x))); };
  using type = kyosu::quaternion_t<T>;
  auto c = type(r, i, j, k);
  TTS_EQUAL(kyosu::proj(c), c);
  auto c1 = type(r, i, eve::minf(as(j)), k);
  auto pc1 = type(eve::inf(as(j)), g(i), g(j), g(k));
  TTS_EQUAL(kyosu::proj(c1), pc1);
};
