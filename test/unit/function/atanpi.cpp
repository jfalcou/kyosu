//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::atanpi over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-1,1), tts::randoms(-1,1)
                              , tts::randoms(-1,1), tts::randoms(-1,1)
                              )
              )
<typename T>(T a0, T a1, T a2, T a3)
{
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r  = T(a0);
  auto c  = ce_t(a0,a1);
  auto q  = qe_t(a0,a1,a2,a3);

  auto re = kyosu::atanpi[kyosu::real_only](r);
  auto lr = kyosu::atanpi(r);
  auto lc = kyosu::atanpi(c);
  auto lq = kyosu::atanpi(q);
  auto rr = eve::atanpi(r);
  TTS_IEEE_EQUAL(re, rr);
  TTS_RELATIVE_EQUAL(kyosu::tanpi(lr),  kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::tanpi(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::tanpi(lq), q, tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::atanpi[cond][kyosu::real_only](r), kyosu::if_else(cond,  eve::atanpi(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::atanpi[cond](r), kyosu::if_else(cond,  kyosu::atanpi(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::atanpi[cond](c), kyosu::if_else(cond,  kyosu::atanpi(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::atanpi[cond](q), kyosu::if_else(cond,  kyosu::atanpi(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::atanpi[cond](r, 2), kyosu::if_else(cond,  kyosu::atanpi(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::atanpi[cond](c, 2), kyosu::if_else(cond,  kyosu::atanpi(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::atanpi[cond](q, 2), kyosu::if_else(cond,  kyosu::atanpi(q, 2), q), tts::prec<T>());
};
