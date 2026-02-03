//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::asecpi over quaternion",
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
  auto rr = eve::asecpi(r);
  auto re = kyosu::asecpi[kyosu::real_only](r);
  TTS_IEEE_EQUAL(re, rr);

  auto lr = kyosu::asecpi(r);
  auto lc = kyosu::asecpi(c);
  auto lq = kyosu::asecpi(q);
  TTS_RELATIVE_EQUAL(kyosu::secpi(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::secpi(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::secpi(lq), q, tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::asecpi[cond][kyosu::real_only](r), kyosu::if_else(cond, eve::asecpi(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asecpi[cond](r), kyosu::if_else(cond, kyosu::asecpi(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asecpi[cond](c), kyosu::if_else(cond, kyosu::asecpi(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asecpi[cond](q), kyosu::if_else(cond, kyosu::asecpi(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::asecpi[cond](r, 2), kyosu::if_else(cond, kyosu::asecpi(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asecpi[cond](c, 2), kyosu::if_else(cond, kyosu::asecpi(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asecpi[cond](q, 2), kyosu::if_else(cond, kyosu::asecpi(q, 2), q), tts::prec<T>());
};
