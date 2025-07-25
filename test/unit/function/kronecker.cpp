//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::kronecker over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             )
              )
(auto r0, auto r1)
{
  TTS_EQUAL(kyosu::kronecker(r0, r1), kyosu::if_else(r0 == r1, kyosu::one(kyosu::as(r0)), kyosu::zero));
  TTS_EQUAL(kyosu::kronecker(r0, r1, r1), kyosu::if_else(r0 == r1, kyosu::one(kyosu::as(r0)), kyosu::zero));
  TTS_EQUAL(kyosu::kronecker(r1, r1, r1), kyosu::one(kyosu::as(r1)));
};

TTS_CASE_WITH ( "Check kyosu::kronecker over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             )
              )
<typename T>(T r0, T i0, T r1, T i1)
{
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  TTS_EQUAL(kyosu::kronecker(c0, c1), kyosu::if_else(c0 == c1, kyosu::one(kyosu::as(r0)), kyosu::zero));
  TTS_EQUAL(kyosu::kronecker(c0, c1, r1), kyosu::zero(kyosu::as(r0)));
  TTS_EQUAL(kyosu::kronecker(c1, c1, c1), kyosu::one(kyosu::as(r0)));
};

TTS_CASE_WITH ( "Check kyosu::kronecker over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1)
{
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0,i0,j0,k0);
  auto q1 = type(r1,i1,j1,k1);
  TTS_EQUAL(kyosu::kronecker(q0, q1), kyosu::if_else(q0 == q1, kyosu::one(kyosu::as(r0)), kyosu::zero));
  TTS_EQUAL(kyosu::kronecker(q0, q1, r1), kyosu::zero(kyosu::as(r0)));
  TTS_EQUAL(kyosu::kronecker(q1, q1, q1), kyosu::one(kyosu::as(r0)));
};
