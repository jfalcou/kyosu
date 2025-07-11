//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::pow over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             )
              )
(auto r0, auto r1)
{
  using T =  decltype(r0);
  TTS_RELATIVE_EQUAL(kyosu::pow(r0, r1), kyosu::exp(kyosu::log(r0)*r1), tts::prec<T>(5.0e-3,  1.0e-7));
  TTS_RELATIVE_EQUAL(kyosu::pow(r0, 4),  kyosu::sqr(kyosu::sqr(r0)), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::pow over complex"
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
  TTS_RELATIVE_EQUAL(kyosu::pow(c0, c1), kyosu::exp(kyosu::log(c0)*c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow(r0, c1), kyosu::exp(kyosu::log(r0)*c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow(c0, r1), kyosu::exp(kyosu::log(c0)*r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow(c0, 4),  kyosu::sqr(kyosu::sqr(c0)), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::pow over quaternion"
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
  TTS_RELATIVE_EQUAL(kyosu::pow(q0, q1),  kyosu::exp(kyosu::log(q0)*q1), tts::prec<T>());
};
