//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::asec over quaternion"
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
  auto rr = eve::asec(r);
  auto re = kyosu::asec[kyosu::real_only](r);
  TTS_IEEE_EQUAL(re, rr);

  auto lr = kyosu::asec(r);
  auto lc = kyosu::asec(c);
  auto lq = kyosu::asec(q);
  TTS_RELATIVE_EQUAL(kyosu::sec(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sec(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sec(lq), q, tts::prec<T>());

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::asec[cond][kyosu::real_only](r), kyosu::if_else(cond,  eve::asec(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asec[cond](r), kyosu::if_else(cond,  kyosu::asec(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asec[cond](c), kyosu::if_else(cond,  kyosu::asec(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asec[cond](q), kyosu::if_else(cond,  kyosu::asec(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::asec[cond](r, 2), kyosu::if_else(cond,  kyosu::asec(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asec[cond](c, 2), kyosu::if_else(cond,  kyosu::asec(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::asec[cond](q, 2), kyosu::if_else(cond,  kyosu::asec(q, 2), q), tts::prec<T>());
};
