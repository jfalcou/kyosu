//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::exp10 over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(kyosu::exp10(data), eve::exp10(data), 0.5);
};

TTS_CASE_WITH ( "Check kyosu::exp10 over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using ce_t = kyosu::as_complex_t<T>;
  auto c = ce_t(r,i);
  TTS_RELATIVE_EQUAL(kyosu::exp10(c), kyosu::exp(eve::log_10(eve::as<T>())*c), 1e-5);
  using qe_t = kyosu::as_quaternion_t<T>;
  auto q = qe_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::exp10(q), kyosu::exp(eve::log_10(eve::as<T>())*q), 1e-5);
};
