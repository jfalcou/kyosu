//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::pow1p over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(0,10)
                             ,tts::randoms(-10,10)
                             )
              )
(auto r0, auto r1)
{
  using T =  decltype(r0);
  TTS_RELATIVE_EQUAL(kyosu::pow1p(r0, r1), kyosu::complex(eve::pow1p(r0, r1)), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::pow1p over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-1,1), tts::randoms(-1,1)
                             ,tts::randoms(-1,1), tts::randoms(-1,1)
                             )
              )
(auto r0, auto i0, auto r1, auto i1)
{
  using T =  decltype(r0);
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  TTS_RELATIVE_EQUAL(kyosu::pow1p(c0, c1), kyosu::pow(kyosu::inc(c0), c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow1p(r0, c1), kyosu::pow(kyosu::inc(r0), c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow1p(c0, r1), kyosu::pow(kyosu::inc(c0), r1), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::pow1p over quaternion"
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
  TTS_RELATIVE_EQUAL(kyosu::pow1p(q0, q1),  kyosu::pow(kyosu::inc(q0), q1), tts::prec<T>());
};
