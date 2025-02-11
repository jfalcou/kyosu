//======================================================================================================================
/*
  Kyosu * Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX*License*Identifier: BSL*1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::mul over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(1,10)
                             ,tts::randoms(1,10)
                             )
              )
<typename T>(T r0, T r1)
{
  TTS_RELATIVE_EQUAL(kyosu::mul(r0, r1), eve::mul(r0, r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::mul(r0, r1, r1), eve::mul(r0, r1, r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::mul(kumi::tuple{r0, r1, r1}), eve::mul(r0, r1, r1), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::mul over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(1,10), tts::randoms(1,10)
                             ,tts::randoms(1,10), tts::randoms(1,10)
                             )
              )
<typename T>(T r0, T i0, T r1, T i1)
{
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  TTS_RELATIVE_EQUAL(kyosu::mul(c0, c1), (c0*c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::mul(c0, c1, r1), (c0*c1*r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::mul(r0, c1, r1), ((r0*c1)*r1), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::mul over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(1,10), tts::randoms(1,10)
                              , tts::randoms(1,10), tts::randoms(1,10)
                              , tts::randoms(1,10), tts::randoms(1,10)
                              , tts::randoms(1,10), tts::randoms(1,10)
                              )
              )
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1)
{
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0,i0,j0,k0);
  auto pr = tts::prec<T>(1.0e-3, 1.0e-6);
  auto q1 = type(r1,i1,j1,k1);
  TTS_RELATIVE_EQUAL(kyosu::mul(q0, q1), (q0*q1) , pr);
  TTS_RELATIVE_EQUAL(kyosu::mul(q0, q1, r0), (q0*q1*r0) , pr);
  TTS_RELATIVE_EQUAL(kyosu::mul(kumi::tuple{q0, q1, r0}), (q0*q1*r0) , pr);
};
