//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::pure over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::pure(data), eve::zero(eve::as(data)));
};

TTS_CASE_WITH("Check kyosu::pure over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  auto pz = kyosu::pure(kyosu::complex(r, i));
  TTS_EQUAL(kyosu::real(pz), kyosu::zero(kyosu::as(r)));
  TTS_EQUAL(kyosu::imag(pz), i);
};

TTS_CASE_WITH("Check kyosu::pure over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
(auto r, auto i, auto j, auto k)
{
  auto pq = kyosu::pure(kyosu::quaternion(r, i, j, k));
  TTS_EQUAL(kyosu::real(pq), kyosu::zero(kyosu::as(r)));
  TTS_EQUAL(kyosu::ipart(pq), i);
  TTS_EQUAL(kyosu::jpart(pq), j);
  TTS_EQUAL(kyosu::kpart(pq), k);
};

TTS_CASE_WITH("Check kyosu::pure over octonion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))<typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  auto po = kyosu::pure(type(r, i, j, k, l, li, lj, lk));
  TTS_EQUAL(kyosu::real(po), kyosu::zero(kyosu::as(r)));
  TTS_EQUAL(kyosu::ipart(po), i);
  TTS_EQUAL(kyosu::jpart(po), j);
  TTS_EQUAL(kyosu::kpart(po), k);
  TTS_EQUAL(kyosu::lpart(po), l);
  TTS_EQUAL(kyosu::lipart(po), li);
  TTS_EQUAL(kyosu::ljpart(po), lj);
  TTS_EQUAL(kyosu::lkpart(po), lk);
};
