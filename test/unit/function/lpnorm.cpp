//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::lpnorm over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             ,tts::randoms(1, 3)
                             )
              )
(auto r0, auto r1, auto p)
{
  TTS_EQUAL(kyosu::lpnorm(p, r0, r1), eve::lpnorm(p, r0, r1));
  TTS_EQUAL(kyosu::lpnorm(2, r0, r1), eve::lpnorm(2, r0, r1));
  TTS_EQUAL(kyosu::lpnorm(2, r0, r1), eve::hypot(r0, r1));
  TTS_EQUAL(kyosu::lpnorm(eve::inf(eve::as(r0)), r0, r1), kyosu::maxabs(r0, r1));
};

TTS_CASE_WITH ( "Check kyosu::lpnorm over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(1, 3)
                             )
              )
(auto r0, auto i0, auto r1, auto i1, auto p)
{
  using T = decltype(r0);
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  TTS_RELATIVE_EQUAL(kyosu::lpnorm(p, c0, c1), eve::lpnorm(p, kyosu::abs(c0), kyosu::abs(c1)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::lpnorm(2, c0, c1), kyosu::hypot(c0, c1) , tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::lpnorm over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              ,tts::randoms(1, 3)
                              )
              )
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1, T p)
{
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0,i0,j0,k0);
  auto q1 = type(r1,i1,j1,k1);
  TTS_RELATIVE_EQUAL(kyosu::lpnorm(p, q0, q1), eve::lpnorm(p, kyosu::abs(q0), kyosu::abs(q1)), tts::prec<T>());
};
