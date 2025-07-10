//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::asin over quaternion"
              , kyosu::scalar_real_types
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

  auto lr = kyosu::asin(r);
  auto lc = kyosu::asin(c);
  auto lq = kyosu::asin(q);
  auto re = kyosu::asin[kyosu::real_only](r);
  auto rr = eve::asin(r);

  TTS_IEEE_EQUAL(re,  ce_t(rr, eve::if_else(eve::is_nan(rr), eve::nan(eve::as(r)), eve::zero)));
  TTS_RELATIVE_EQUAL(kyosu::sin(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sin(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sin(lq), q, tts::prec<T>());
};
