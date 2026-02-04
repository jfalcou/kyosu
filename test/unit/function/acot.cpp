//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::acot over quaternion",
              kyosu::simd_real_types,
              tts::randoms(-1, 1),
              tts::randoms(-1, 1),
              tts::randoms(-1, 1),
              tts::randoms(-1, 1)

)
<typename T>(T a0, T a1, T a2, T a3)
{
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r = T(a0);
  auto c = ce_t(a0, a1);
  auto q = qe_t(a0, a1, a2, a3);

  auto re = kyosu::acot[kyosu::real_only](r);
  auto lr = kyosu::acot(r);
  auto lc = kyosu::acot(c);
  auto lq = kyosu::acot(q);
  auto rr = eve::acot(r);
  TTS_IEEE_EQUAL(re, rr);
  TTS_RELATIVE_EQUAL(kyosu::cot(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::cot(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::cot(lq), q, tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::acot[cond][kyosu::real_only](r), kyosu::if_else(cond, eve::acot(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acot[cond](r), kyosu::if_else(cond, kyosu::acot(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acot[cond](c), kyosu::if_else(cond, kyosu::acot(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acot[cond](q), kyosu::if_else(cond, kyosu::acot(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::acot[cond](r, 2), kyosu::if_else(cond, kyosu::acot(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acot[cond](c, 2), kyosu::if_else(cond, kyosu::acot(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acot[cond](q, 2), kyosu::if_else(cond, kyosu::acot(q, 2), q), tts::prec<T>());
};
