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
              , tts::generate(tts::between(-10,10)
                             ,tts::between(-10,10)
                             )
              )
(auto r0, auto r1)
{
  TTS_EQUAL(kyosu::pow1p(r0, r1), eve::pow1p(r0, r1));
  TTS_RELATIVE_EQUAL(kyosu::pow1p(r0, 4),  kyosu::sqr(kyosu::sqr(eve::inc(r0))), 1.0e-5);
};

TTS_CASE_WITH ( "Check kyosu::pow1p over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10)
                             ,tts::between(-10,10), tts::between(-10,10)
                             )
              )
(auto r0, auto i0, auto r1, auto i1)
{
  auto c0 = kyosu::to_complex(r0,i0);
  auto c1 = kyosu::to_complex(r1,i1);
  TTS_RELATIVE_EQUAL(kyosu::pow1p(c0, c1), kyosu::exp(c1*kyosu::log(kyosu::inc(c0))), 1e-5);
  TTS_RELATIVE_EQUAL(kyosu::pow1p(r0, c1), kyosu::exp(c1*kyosu::log(kyosu::inc(r0))), 1e-5);
  TTS_RELATIVE_EQUAL(kyosu::pow1p(c0, r1), kyosu::exp(r1*kyosu::log(kyosu::inc(c0))), 1e-5);
//  TTS_RELATIVE_EQUAL(kyosu::pow1p(c0, 4u),  kyosu::dec(c0*kyosu::sqr(kyosu::sqr(c0)), 1.0e-5);
};

TTS_CASE_WITH ( "Check kyosu::pow1p over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1)
{
  using type = kyosu::as_quaternion_t<T>;
  auto q0 = type(r0,i0,j0,k0);
  auto q1 = type(r1,i1,j1,k1);
  TTS_RELATIVE_EQUAL(kyosu::pow1p(q0, q1),  kyosu::exp(q1*kyosu::log(kyosu::inc(q0))), 1e-5);
//  TTS_RELATIVE_EQUAL(kyosu::pow1p(q0, 4), kyosu::sqr(kyosu::sqr(q0)), 1.0e-5);
};
