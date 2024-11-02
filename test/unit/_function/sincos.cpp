//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sin over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  {
    auto [s, c] = kyosu::sincos(r);
    TTS_RELATIVE_EQUAL(s, kyosu::sin(r), 1e-5);
    TTS_RELATIVE_EQUAL(c, kyosu::cos(r), 1e-5);
  }
  {
    using ke_t = kyosu::complex_t<T>;
    auto cq= ke_t(r,i);
    auto [s, c] = kyosu::sincos(cq);
    TTS_RELATIVE_EQUAL(s, kyosu::sin(cq), 1e-5);
    TTS_RELATIVE_EQUAL(c, kyosu::cos(cq), 1e-5);
  }
  {
    using ke_t = kyosu::quaternion_t<T>;
    auto q = ke_t(r,i,j,k);
    auto [s, c] = kyosu::sincos(q);
    TTS_RELATIVE_EQUAL(s, kyosu::sin(q), 1e-5);
    TTS_RELATIVE_EQUAL(c, kyosu::cos(q), 1e-5);
  }
};
