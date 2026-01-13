//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::geommean over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(0,10)
                             ,tts::randoms(0,10)
                             )
              )
  <typename T>(T r0, T r1)
{
  TTS_EQUAL(kyosu::geommean(r0), r0);
  TTS_EQUAL(kyosu::geommean(r0, r1), eve::geommean(r0, r1));
  TTS_EQUAL(kyosu::geommean(r0, r1, r1), eve::geommean(r0, r1, r1));
  auto cond = eve::is_ltz(r0);
  TTS_EQUAL(kyosu::geommean[cond](r0, r1, r1), eve::geommean[cond](r0, r1, r1));
};

TTS_CASE_WITH ( "Check kyosu::geommean over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             )
              )
<typename T>(T r0, T i0, T r1, T i1)
{
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  TTS_EQUAL(kyosu::geommean(c0), c0);
  using kyosu::sqrt;
  using kyosu::cbrt;
  auto pr = tts::prec<T>(1.0e-1, 1.0e-6);
  TTS_RELATIVE_EQUAL(kyosu::geommean(c0, c1), sqrt(c0*c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::geommean(c0, c1, r1), cbrt(c0*c1*r1), pr);
  TTS_RELATIVE_EQUAL(kyosu::geommean(r0, c1, r1), cbrt(r0*c1*r1), pr);

  auto cond = eve::is_ltz(r0);
  TTS_EQUAL(kyosu::geommean[cond](c0, c1), kyosu::if_else(cond, kyosu::geommean(c0, c1), c0));
};
