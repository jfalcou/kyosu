//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::signnz over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_ULP_EQUAL(kyosu::signnz(data), eve::signnz(data), 0.5);
};

TTS_CASE_WITH("Check kyosu::signnz over quaternion",
              kyosu::simd_real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r, T i, T j, T k)
{
  using ke_t = kyosu::quaternion_t<T>;
  auto q = ke_t(r, i, j, k);
  TTS_RELATIVE_EQUAL(kyosu::signnz(q), q / kyosu::abs(q), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::signnz(kyosu::quaternion(T(0.0))), kyosu::quaternion(T(1.0)), tts::prec<T>());
};
