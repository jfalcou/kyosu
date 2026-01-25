//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check kyosu::agd over cayley_dickson"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(0, 1.5), tts::randoms(-10,10)
                              , tts::randoms(0, 1.5), tts::randoms(-10,10)
                              )
              )
<typename T>(T a0, T a1, T a2, T a3)
{
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;
  auto pr = tts::prec<T>(2.0e-2, 1.0e-7);
  auto r  = T(a0);
  auto c  = ce_t(a0,a1);
  auto q  = qe_t(a0,a1,a2,a3);

  auto re = kyosu::agd[kyosu::real_only](r);
  auto lr = kyosu::agd(r);
  auto lc = kyosu::agd(c);
  auto lq = kyosu::agd(q);
  auto rr = eve::agd(r);

  TTS_IEEE_EQUAL(re, rr);
  TTS_RELATIVE_EQUAL(kyosu::gd(lr), ce_t(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::gd(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::gd(lq), q, pr);

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::agd[cond][kyosu::real_only](r), kyosu::if_else(cond,  eve::agd(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::agd[cond](r), kyosu::if_else(cond,  kyosu::agd(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::agd[cond](c), kyosu::if_else(cond,  kyosu::agd(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::agd[cond](q), kyosu::if_else(cond,  kyosu::agd(q), q), pr);
};
