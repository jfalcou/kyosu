//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::rising_factorial over cayley_dickson"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(0,10), tts::randoms(0,10)
                              , tts::randoms(0,10), tts::randoms(0,10),
                                tts::randoms(0,10), tts::randoms(0,10)
                              , tts::randoms(0,10), tts::randoms(0,10)
                              )
              )
<typename T>(T a0, T a1, T a2 , T a3, T  b0, T b1, T b2, T b3)
{
  auto use = [](auto ...){};
  use(b0, b1, b2, b3);
  use(a0, a1, a2, a3);

  auto myrising_factorial = [](auto aa,  auto bb){return kyosu::tgamma(aa+bb)/kyosu::tgamma(aa); };
  using qe_t = kyosu::quaternion_t<T>;

  auto r0  = T(a0);
  auto c0  = kyosu::complex(a0,a1);
  auto q0  = qe_t(a0,a1,a2,a3);
  auto r1  = T(b0);
  auto c1  = kyosu::complex(b0,b1);
  auto q1  = qe_t(b0,b1,b2,b3);

  auto rr = eve::rising_factorial(r0, r1);
  auto re = kyosu::rising_factorial[kyosu::real_only](r0, r1);
  TTS_IEEE_EQUAL(re, rr);

  auto lr = kyosu::rising_factorial(r0, r1);
  auto lc = kyosu::rising_factorial(c0, c1);
  auto lq = kyosu::rising_factorial(q0, q1);
  use(lr, lc, lq, q0, q1);
  auto pr =  tts::prec<T>(4.0e-2, 1.0e-7);
  TTS_RELATIVE_EQUAL(lr, kyosu::inject(eve::rising_factorial(r0, r1)), pr);
  TTS_RELATIVE_EQUAL(lc, myrising_factorial(c0, c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(lq, myrising_factorial(q0, q1), pr);

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::rising_factorial[cond][kyosu::real_only](r0, r1), kyosu::if_else(cond,  eve::rising_factorial(r0, r1), r0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial[cond](r0, r1), kyosu::if_else(cond,  kyosu::rising_factorial(r0, r1), kyosu::complex(r0)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial[cond](c0, c1), kyosu::if_else(cond,  kyosu::rising_factorial(c0, c1), c0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial[cond](q0, q1), kyosu::if_else(cond,  kyosu::rising_factorial(q0, q1), q0), tts::prec<T>());
};
