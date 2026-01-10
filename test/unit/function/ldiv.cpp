//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::ldiv over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             )
              )
<typename T>(T r0, T r1)
{
  TTS_EQUAL(kyosu::ldiv(r0), eve::rec(r0));
  TTS_RELATIVE_EQUAL(kyosu::ldiv(r0, r1), r1/r0, tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::ldiv over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             )
              )
<typename T>(T r0, T i0, T r1, T i1)
{
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  TTS_EQUAL(kyosu::ldiv(c0), kyosu::rec(c0));
  TTS_RELATIVE_EQUAL(kyosu::ldiv(c0, c1), c1/c0, tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::ldiv over quaternion"
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
  TTS_EQUAL(kyosu::ldiv(q0), kyosu::rec(q0));
  TTS_RELATIVE_EQUAL(kyosu::ldiv(q0, q1), kyosu::conj(q0)*q1/kyosu::sqr_abs(q0) , tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::ldiv(q0, q1, r0), kyosu::ldiv(q0, (q1*r0)) ,  tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::div(kumi::tuple{q0, q1, r0}), (q0/(q1*r0)) ,  tts::prec<T>());
 };
