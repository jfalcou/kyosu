//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::acsc over quaternion",
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

  auto rr = eve::acsc(r);
  auto re = kyosu::acsc[kyosu::real_only](r);
  TTS_IEEE_EQUAL(re, rr);

  auto lr = kyosu::acsc(r);
  auto lc = kyosu::acsc(c);
  auto lq = kyosu::acsc(q);
  TTS_RELATIVE_EQUAL(kyosu::csc(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::csc(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::csc(lq), q, tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::acsc[cond][kyosu::real_only](r), kyosu::if_else(cond, eve::acsc(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acsc[cond](r), kyosu::if_else(cond, kyosu::acsc(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acsc[cond](c), kyosu::if_else(cond, kyosu::acsc(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acsc[cond](q), kyosu::if_else(cond, kyosu::acsc(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::acsc[cond](r, 2), kyosu::if_else(cond, kyosu::acsc(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acsc[cond](c, 2), kyosu::if_else(cond, kyosu::acsc(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::acsc[cond](q, 2), kyosu::if_else(cond, kyosu::acsc(q, 2), q), tts::prec<T>());
};
