//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::atan over quaternion",
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

  auto re = kyosu::atan[kyosu::real_only](r);
  auto lr = kyosu::atan(r);
  auto lc = kyosu::atan(c);
  auto lq = kyosu::atan(q);
  auto rr = eve::atan(r);
  TTS_IEEE_EQUAL(re, rr);
  TTS_RELATIVE_EQUAL(kyosu::tan(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::tan(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::tan(lq), q, tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::atan[cond][kyosu::real_only](r), kyosu::if_else(cond, eve::atan(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::atan[cond](r), kyosu::if_else(cond, kyosu::atan(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::atan[cond](c), kyosu::if_else(cond, kyosu::atan(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::atan[cond](q), kyosu::if_else(cond, kyosu::atan(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::atan[cond](r, 2), kyosu::if_else(cond, kyosu::atan(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::atan[cond](c, 2), kyosu::if_else(cond, kyosu::atan(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::atan[cond](q, 2), kyosu::if_else(cond, kyosu::atan(q, 2), q), tts::prec<T>());
};
