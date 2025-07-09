//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::acos over quaternion"
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

  auto re = kyosu::acos[kyosu::real_only](r);
  auto lr = kyosu::acos(r);
  auto lc = kyosu::acos(c);
  auto lq = kyosu::acos(q);
  auto rr = eve::acos(r);

  TTS_IEEE_EQUAL(re,  ce_t(rr, eve::if_else(eve::is_nan(rr), eve::nan(eve::as(r)), eve::zero)));
  TTS_RELATIVE_EQUAL(kyosu::cos(lr), ce_t(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::cos(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::cos(lq), q, tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::acos[cond](r), kyosu::if_else(cond,  kyosu::acos(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acos[cond](c), kyosu::if_else(cond,  kyosu::acos(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acos[cond](q), kyosu::if_else(cond,  kyosu::acos(q), q), tts::prec<T>());


};
