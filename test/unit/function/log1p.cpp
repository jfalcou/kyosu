//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::exp over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T a0, T a1, T a2, T a3)
{
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r  = T(a0);
  auto c  = ce_t(a0,a1);
  auto q  = qe_t(a0,a1,a2,a3);

  auto rr = eve::log1p(r);
  auto re = kyosu::log1p[kyosu::real_only](r);
  TTS_IEEE_EQUAL(re,  ce_t(rr, eve::if_else(eve::is_nan(rr), eve::nan(eve::as(rr)), eve::zero)));

  TTS_RELATIVE_EQUAL( kyosu::log1p(r), kyosu::log(kyosu::inc(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log1p(c), kyosu::log(kyosu::inc(c)), tts::prec<T>());
  TTS_RELATIVE_EQUAL( kyosu::log1p(q), kyosu::log(kyosu::inc(q)), tts::prec<T>());
};
