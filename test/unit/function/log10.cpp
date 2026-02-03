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

  auto rr = eve::log10(r);
  auto re = kyosu::log10[kyosu::real_only](r);
  TTS_IEEE_EQUAL(re, rr);

  auto lr = kyosu::log10(r);
  auto lc = kyosu::log10(c);
  auto lq = kyosu::log10(q);
  TTS_RELATIVE_EQUAL(kyosu::exp10(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::exp10(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::exp10(lq), q, 2e-4);

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::log10[cond][kyosu::real_only](r), kyosu::if_else(cond, eve::log10(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log10[cond](r), kyosu::if_else(cond, kyosu::log10(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log10[cond](c), kyosu::if_else(cond, kyosu::log10(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log10[cond](q), kyosu::if_else(cond, kyosu::log10(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::log10[cond](r, 2), kyosu::if_else(cond, kyosu::log10(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log10[cond](c, 2), kyosu::if_else(cond, kyosu::log10(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log10[cond](q, 2), kyosu::if_else(cond, kyosu::log10(q, 2), q), tts::prec<T>());
};
