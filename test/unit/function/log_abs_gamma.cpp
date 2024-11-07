//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::tgamma over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(1,2), tts::randoms(1,2)
                              , tts::randoms(1,2), tts::randoms(1,2)
                              )
              )
<typename T>(T a0, T a1, T a2, T a3)
{
  auto prec = sizeof(eve::element_type_t<T>) == 4 ? 1.0e-3 : 1.0e-6;
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r  = T(a0);
  auto c  = ce_t(a0,a1);
  auto q  = qe_t(a0,a1,a2,a3);

  TTS_RELATIVE_EQUAL(kyosu::log_abs_gamma(r), eve::log(kyosu::abs(kyosu::tgamma(r))), prec);
  TTS_RELATIVE_EQUAL(kyosu::log_abs_gamma(c), eve::log(kyosu::abs(kyosu::tgamma(c))), prec);
  TTS_RELATIVE_EQUAL(kyosu::log_abs_gamma(q), eve::log(kyosu::abs(kyosu::tgamma(q))), prec);
};