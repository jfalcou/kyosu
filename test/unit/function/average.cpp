//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::average over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             )
              )
(auto r0, auto r1)
{
  using T =  decltype(r0);
  TTS_EQUAL(kyosu::average(r0, r1), eve::average(r0, r1));
  TTS_EQUAL(kyosu::average(r0, r1, r1), eve::average(r0, r1, r1));
  auto cond = eve::is_ltz(r0);
  TTS_RELATIVE_EQUAL(kyosu::average[cond](r0, r1), kyosu::if_else(cond, (r0+r1)*T(0.5), r0), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::average over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             )
              )
<typename T>(T r0, T i0, T r1, T i1)
{
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  TTS_RELATIVE_EQUAL(kyosu::average(c0, c1), (c0+c1)*T(0.5), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::average(c0, c1, r1), (c0+c1+r1)/T(3), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::average(r0, c1, r1), (r0+c1+r1)/T(3), tts::prec<T>());

  auto cond = eve::is_ltz(r0);
  TTS_RELATIVE_EQUAL(kyosu::average[cond](c0, c1), kyosu::if_else(cond, (c0+c1)*T(0.5), c0), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::average over quaternion"
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
  TTS_RELATIVE_EQUAL(kyosu::average(q0, q1), (q0+q1)*T(0.5) , tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::average(q0, q1, r0), (q0+q1+r0)/T(3) , tts::prec<T>());
  auto cond = eve::is_ltz(r0);
  TTS_RELATIVE_EQUAL(kyosu::average[cond](q0, q1), kyosu::if_else(cond, (q0+q1)*T(0.5), q0), tts::prec<T>());
};
