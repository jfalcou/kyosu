//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::exp over quaternion",
              kyosu::simd_real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T a0, T a1, T a2, T a3)
{
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r = T(a0);
  auto c = ce_t(a0, a1);
  auto q = qe_t(a0, a1, a2, a3);

  auto rr = eve::log1p(r);
  auto re = kyosu::log1p[kyosu::real_only](r);
  TTS_IEEE_EQUAL(re, rr);

  TTS_RELATIVE_EQUAL(kyosu::log1p(r), kyosu::log(kyosu::inc(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log1p(c), kyosu::log(kyosu::inc(c)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log1p(q), kyosu::log(kyosu::inc(q)), tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::log1p[cond][kyosu::real_only](r), kyosu::if_else(cond, eve::log1p(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log1p[cond](r), kyosu::if_else(cond, kyosu::log1p(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log1p[cond](c), kyosu::if_else(cond, kyosu::log1p(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log1p[cond](q), kyosu::if_else(cond, kyosu::log1p(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::log1p[cond](r, 2), kyosu::if_else(cond, kyosu::log1p(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log1p[cond](c, 2), kyosu::if_else(cond, kyosu::log1p(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log1p[cond](q, 2), kyosu::if_else(cond, kyosu::log1p(q, 2), q), tts::prec<T>());
};
