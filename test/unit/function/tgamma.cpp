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
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r  = T(a0);
  auto c  = ce_t(a0,a1);
  auto q  = qe_t(a0,a1,a2,a3);

  TTS_RELATIVE_EQUAL(kyosu::tgamma(kyosu::inc(r)), r*kyosu::tgamma(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::tgamma(kyosu::inc(c)), c*kyosu::tgamma(c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::tgamma(kyosu::inc(q)), q*kyosu::tgamma(q), tts::prec<T>());
  auto cpl = [](auto z){ return kyosu::tgamma(kyosu::oneminus(z))*kyosu::tgamma(z)*kyosu::sinpi(z); };
  TTS_RELATIVE_EQUAL(cpl(r), kyosu::pi(eve::as(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(cpl(c), kyosu::pi(eve::as(c)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(cpl(q), kyosu::pi(eve::as(q)), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::real(kyosu::tgamma(r, T(2.0))), eve::gamma_p(r, T(2.0)), tts::prec<T>());


};
