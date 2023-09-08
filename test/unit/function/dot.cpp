//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::dot over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10)
                             ,tts::between(-10,10)
                             )
              )
(auto r0, auto r1)
{
  TTS_EQUAL(kyosu::dot(r0, r1), r0*r1);
};

TTS_CASE_WITH ( "Check kyosu::dot over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10)
                             ,tts::between(-10,10), tts::between(-10,10)
                             )
              )
<typename T>(T r0, T i0, T r1, T i1)
{
  auto c0 = kyosu::to_complex(r0,i0);
  auto c1 = kyosu::to_complex(r1,i1);
  TTS_RELATIVE_EQUAL(kyosu::dot(c0, c1)
                    , kyosu::real(c0)*kyosu::real(c1)+kyosu::imag(c0)*kyosu::imag(c1), 1e-7);
};

TTS_CASE_WITH ( "Check kyosu::dot over quaternion"
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
  TTS_RELATIVE_EQUAL(kyosu::dot(q0, q1),  kyosu::real(q0)*kyosu::real(q1)+
                                          kyosu::ipart(q0)*kyosu::ipart(q1)+
                                          kyosu::jpart(q0)*kyosu::jpart(q1)+
                                          kyosu::kpart(q0)*kyosu::kpart(q1), 1e-7);
};
