//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::tgamma over quaternion",
              kyosu::simd_real_types,
              tts::randoms(1, 2),
              tts::randoms(1, 2),
              tts::randoms(1, 2),
              tts::randoms(1, 2)

)
<typename T>(T a0, T a1, T a2, T a3)
{
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r = T(a0);
  auto c = ce_t(a0, a1);
  auto q = qe_t(a0, a1, a2, a3);
  auto re = kyosu::log_gamma[kyosu::real_only](r);
  auto rr = eve::log_gamma(r);

  TTS_IEEE_EQUAL(re, rr);

  TTS_RELATIVE_EQUAL(kyosu::log_gamma(r), kyosu::log(kyosu::tgamma(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log_gamma(c), kyosu::log(kyosu::tgamma(c)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log_gamma(q), kyosu::log(kyosu::tgamma(q)), tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::log_gamma[cond][kyosu::real_only](r), kyosu::if_else(cond, eve::log_gamma(r), r),
                     tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log_gamma[cond](r), kyosu::if_else(cond, kyosu::log_gamma(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log_gamma[cond](c), kyosu::if_else(cond, kyosu::log_gamma(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log_gamma[cond](q), kyosu::if_else(cond, kyosu::log_gamma(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::log_gamma[cond](r, 2), kyosu::if_else(cond, kyosu::log_gamma(r, 2), ce_t(r)),
                     tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log_gamma[cond](c, 2), kyosu::if_else(cond, kyosu::log_gamma(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log_gamma[cond](q, 2), kyosu::if_else(cond, kyosu::log_gamma(q, 2), q), tts::prec<T>());
};
