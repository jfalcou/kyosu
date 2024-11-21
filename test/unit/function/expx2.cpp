//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::expx2 over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(0.5,2.0), tts::randoms(0.5,2.0)
                              , tts::randoms(0.5,2.0), tts::randoms(0.5,2.0)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  TTS_RELATIVE_EQUAL(kyosu::expx2(r), kyosu::exp(kyosu::sqr(r)), tts::prec<T>());
  using ce_t = kyosu::complex_t<T>;
  auto c = ce_t(r,i);
  TTS_RELATIVE_EQUAL(kyosu::expx2(c), kyosu::exp(kyosu::sqr(c)), tts::prec<T>());
  using qe_t = kyosu::quaternion_t<T>;
  auto q = qe_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::expx2(q), kyosu::exp(kyosu::sqr(q)), tts::prec<T>());
};
