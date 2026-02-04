//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::is_nez over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::is_nez(data), eve::is_nez(data));
};

TTS_CASE_WITH("Check kyosu::is_nez over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  TTS_EQUAL(kyosu::is_nez(kyosu::complex(r, i)), eve::is_nez(r) && eve::is_nez(i));
  auto z(eve::zero(eve::as(r)));
  TTS_EQUAL(kyosu::is_nez(z), eve::false_(eve::as(r)));
};

TTS_CASE_WITH("Check kyosu::is_nez over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto z(eve::zero(eve::as(r)));
  TTS_EQUAL(kyosu::is_nez(type(r, i, j, k)), eve::is_nez(r) && eve::is_nez(i) && eve::is_nez(j) && eve::is_nez(k));
  TTS_EQUAL(kyosu::is_nez(z), eve::false_(eve::as(r)));
};

TTS_CASE_WITH("Check kyosu::is_nez over octonion",
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
  auto z(eve::zero(eve::as(r)));
  TTS_EQUAL(kyosu::is_nez(type(r, i, j, k, l, li, lj, lk)), eve::is_nez(r) && eve::is_nez(i) && eve::is_nez(j) &&
                                                              eve::is_nez(k) && eve::is_nez(l) && eve::is_nez(li) &&
                                                              eve::is_nez(lj) && eve::is_nez(lk));
  TTS_EQUAL(kyosu::is_nez(z), eve::false_(eve::as(r)));
};
