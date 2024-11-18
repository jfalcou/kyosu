//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sinh over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  {
    auto [s, c] = kyosu::sinhcosh(r);
    TTS_RELATIVE_EQUAL(s, kyosu::sinh(r), 1e-5);
    TTS_RELATIVE_EQUAL(c, kyosu::cosh(r), 2e-5);
  }
  {
    using ke_t = kyosu::complex_t<T>;
    auto cq= ke_t(r,i);
    auto [s, c] = kyosu::sinhcosh(cq);
    TTS_RELATIVE_EQUAL(s, kyosu::sinh(cq), 1e-5);
    TTS_RELATIVE_EQUAL(c, kyosu::cosh(cq), 1e-5);
  }
  {
    using ke_t = kyosu::quaternion_t<T>;
    auto q = ke_t(r,i,j,k);
    auto [s, c] = kyosu::sinhcosh(q);
    TTS_RELATIVE_EQUAL(s, kyosu::sinh(q), 1e-5);
    TTS_RELATIVE_EQUAL(c, kyosu::cosh(q), 1e-5);
  }
};
