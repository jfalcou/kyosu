//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::exp2 over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(kyosu::exp2(data), eve::exp2(data), 0.5);
};

TTS_CASE_WITH ( "Check kyosu::exp2 over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using ce_t = kyosu::complex_t<T>;
  auto c = ce_t(r,i);
  TTS_RELATIVE_EQUAL(kyosu::exp2(c), kyosu::exp(eve::log_2(eve::as<T>())*c), tts::prec<T>());
  using qe_t = kyosu::quaternion_t<T>;
  auto q = qe_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::exp2(q), kyosu::exp(eve::log_2(eve::as<T>())*q), tts::prec<T>());
};
