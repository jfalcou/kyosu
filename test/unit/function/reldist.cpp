//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::reldist over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             )
              )
(auto r0, auto r1)
{
  TTS_EQUAL(kyosu::reldist(r0, r1), eve::reldist(r0, r1));
};

TTS_CASE_WITH ( "Check kyosu::reldist over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             )
              )
(auto r0, auto i0, auto r1, auto i1)
{
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  using kyosu::abs;
  auto one = eve::one(eve::as(r0));
  TTS_RELATIVE_EQUAL(kyosu::reldist(c0, c1), abs(c0-c1)/eve::max(abs(c0), abs(c1), one), 1e-7);
};

TTS_CASE_WITH ( "Check kyosu::reldist over quaternion"
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
  using kyosu::abs;
  auto one = eve::one(eve::as(r0));
  TTS_RELATIVE_EQUAL(kyosu::reldist(q0, q1), abs(q0-q1)/eve::max(abs(q0), abs(q1), one), 1e-7);
};
