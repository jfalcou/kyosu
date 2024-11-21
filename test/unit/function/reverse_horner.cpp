//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::reverse_horner over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             ,tts::randoms(0, 1)
                             )
              )
(auto r0, auto r1, auto r2, auto x)
{
  using T =  decltype(r0);
  kumi::tuple a{r2, r1, r0};
  // auto prec = sizeof(eve::element_type_t<decltype(r0)>) == 8 ?  1e-7 : 1.e-3;
  TTS_RELATIVE_EQUAL(kyosu::reverse_horner(x, r2, r1, r0), (r0*x+r1)*x+r2, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::reverse_horner(x, a)         , (r0*x+r1)*x+r2, tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::reverse_horner over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(0, 1), tts::randoms(0, 1)
                             )
              )
(auto r0, auto i0, auto r1, auto i1, auto r2, auto i2, auto x0, auto x1)
{
  using T =  decltype(r0);
  // auto prec = sizeof(eve::element_type_t<decltype(r0)>) == 8 ?  1e-7 : 1.e-3;
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  auto c2 = kyosu::complex(r2,i2);
  auto x  = kyosu::complex(x0, x1);
  kumi::tuple c{c2, c1, c0};
  TTS_RELATIVE_EQUAL(kyosu::reverse_horner(x, c)         , (c0*x+c1)*x+c2, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::reverse_horner(x, c2, c1, c0), (c0*x+c1)*x+c2, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::reverse_horner[eve::right](x, c)         , (c0*x+c1)*x+c2, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::reverse_horner[eve::right](x, c2, c1, c0), (c0*x+c1)*x+c2, tts::prec<T>());

};

TTS_CASE_WITH ( "Check kyosu::reverse_horner over quaternion"
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
  // auto prec = sizeof(eve::element_type_t<decltype(r0)>) == 8 ?  1e-7 : 1.e-3;
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0,i0,j0,k0);
  auto q1 = type(r1,i1,j1,k1);
  auto q2 = type(r2,i2,j2,k2);
  auto x  = type(x0,x1,x2,x3);
  TTS_RELATIVE_EQUAL(kyosu::reverse_horner(x, q2, q1, q0),  (q0*x+q1)*x+q2, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::reverse_horner[eve::right](x, q2, q1, q0),  x*(x*q0+q1)+q2, tts::prec<T>());
  kumi::tuple a{q2, q1, q0};
  TTS_RELATIVE_EQUAL(kyosu::reverse_horner(x, a)         , (q0*x+q1)*x+q2, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::reverse_horner[eve::right](x, a),  x*(x*q0+q1)+q2, tts::prec<T>());

};
