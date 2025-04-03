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
    auto [s, c] = kyosu::sinpicospi(r);
    TTS_RELATIVE_EQUAL(s, kyosu::sinpi(r), tts::prec<T>());
    TTS_RELATIVE_EQUAL(c, kyosu::cospi(r), tts::prec<T>());
  }
  {
    using ke_t = kyosu::complex_t<T>;
    auto cq= ke_t(r,i);
    auto [s, c] = kyosu::sinpicospi(cq);
    TTS_RELATIVE_EQUAL(s, kyosu::sinpi(cq), tts::prec<T>());
    TTS_RELATIVE_EQUAL(c, kyosu::cospi(cq), tts::prec<T>());
  }
  {
    using ke_t = kyosu::quaternion_t<T>;
    auto q = ke_t(r,i,j,k);
    auto [s, c] = kyosu::sinpicospi(q);
    TTS_RELATIVE_EQUAL(s, kyosu::sinpi(q), tts::prec<T>());
    TTS_RELATIVE_EQUAL(c, kyosu::cospi(q), tts::prec<T>());
  }
};
