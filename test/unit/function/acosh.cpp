//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::acosh over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T a0, T a1, T a2, T a3)
{
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r  = T(a0);
  auto c  = ce_t(a0,a1);
  auto q  = qe_t(a0,a1,a2,a3);

  auto re = kyosu::acosh[kyosu::real_only](r);
  auto lr = kyosu::acosh(r);
  auto lc = kyosu::acosh(c);
  auto lq = kyosu::acosh(q);
  auto rr = eve::acosh(r);

  TTS_IEEE_EQUAL(re, rr);
  TTS_RELATIVE_EQUAL(kyosu::cosh(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::cosh(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::cosh(lq), q, tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::acosh[cond][kyosu::real_only](r), kyosu::if_else(cond,  eve::acosh(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acosh[cond](r), kyosu::if_else(cond,  kyosu::acosh(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acosh[cond](c), kyosu::if_else(cond,  kyosu::acosh(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acosh[cond](q), kyosu::if_else(cond,  kyosu::acosh(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::acosh[cond](r, 2), kyosu::if_else(cond,  kyosu::acosh(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acosh[cond](c, 2), kyosu::if_else(cond,  kyosu::acosh(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acosh[cond](q, 2), kyosu::if_else(cond,  kyosu::acosh(q, 2), q), tts::prec<T>());
};
