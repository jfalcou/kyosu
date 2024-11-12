//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::horner over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             ,tts::randoms(0, 1)
                             )
              )
(auto r0, auto r1, auto r2, auto x)
{
  kumi::tuple a{r0, r1, r2};
  TTS_RELATIVE_EQUAL(kyosu::horner(x, r0, r1, r2), (r0*x+r1)*x+r2, 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::horner[eve::right](x, r0, r1, r2), (r0*x+r1)*x+r2, 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::horner(x, a)         , (r0*x+r1)*x+r2, 1e-7);
};

TTS_CASE_WITH ( "Check kyosu::horner over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(0, 1), tts::randoms(0, 1)
                             )
              )
(auto r0, auto i0, auto r1, auto i1, auto r2, auto i2, auto x0, auto x1)
{
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  auto c2 = kyosu::complex(r2,i2);
  auto x  = kyosu::complex(x0, x1);
  TTS_RELATIVE_EQUAL(kyosu::horner(x, c0, c1, c2), (c0*x+c1)*x+c2, 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::horner[eve::right](x, c0, c1, c2), (c0*x+c1)*x+c2, 1e-7);
  kumi::tuple c{c0, c1, c2};
  TTS_RELATIVE_EQUAL(kyosu::horner(x, c)         , (c0*x+c1)*x+c2, 1e-7);

};

TTS_CASE_WITH ( "Check kyosu::horner over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(0, 1), tts::randoms(0, 1)
                              , tts::randoms(0, 1), tts::randoms(0, 1)
                              )
              )
<typename T>(T r0, T i0, T j0, T k0
            , T r1, T i1, T j1, T k1
            , T r2, T i2, T j2, T k2
            , T x0, T x1, T x2, T x3 )
{
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0,i0,j0,k0);
  auto q1 = type(r1,i1,j1,k1);
  auto q2 = type(r2,i2,j2,k2);
  auto x  = type(x0,x1,x2,x3);
  TTS_RELATIVE_EQUAL(kyosu::horner(x, q0, q1, q2),  (q0*x+q1)*x+q2, 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::horner[eve::right](x, q0, q1, q2),  x*(x*q0+q1)+q2, 1e-7);
//   kumi::tuple a{q0, q1, q2};
//   TTS_RELATIVE_EQUAL(kyosu::horner(x, a)            , (q0*x+q1)*x+q2, 1e-7);
//   TTS_RELATIVE_EQUAL(kyosu::horner[eve::right](x, a),  x*(x*q0+q1)+q2, 1e-7);

};
