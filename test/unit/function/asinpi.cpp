//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::asinpi over quaternion",
              kyosu::scalar_real_types,
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

  auto lr = kyosu::asinpi(r);
  auto lc = kyosu::asinpi(c);
  auto lq = kyosu::asinpi(q);

  auto re = kyosu::asinpi[kyosu::real_only](r);
  auto rr = eve::asinpi(r);

  TTS_IEEE_EQUAL(re, rr);
  TTS_RELATIVE_EQUAL(kyosu::sinpi(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sinpi(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sinpi(lq), q, tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::asinpi[cond][kyosu::real_only](r), kyosu::if_else(cond, eve::asinpi(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asinpi[cond](r), kyosu::if_else(cond, kyosu::asinpi(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asinpi[cond](c), kyosu::if_else(cond, kyosu::asinpi(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asinpi[cond](q), kyosu::if_else(cond, kyosu::asinpi(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::asinpi[cond](r, 2), kyosu::if_else(cond, kyosu::asinpi(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asinpi[cond](c, 2), kyosu::if_else(cond, kyosu::asinpi(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asinpi[cond](q, 2), kyosu::if_else(cond, kyosu::asinpi(q, 2), q), tts::prec<T>());
};
