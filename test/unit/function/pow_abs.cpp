//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::pow_abs over real", kyosu::simd_real_types, tts::randoms(-10, 10), tts::randoms(-10, 10)

)
<typename T>(T r0, T r1)
{
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(r0, r1), eve::pow_abs(r0, r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(r0, 5.3), eve::pow_abs(r0, 5.3), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(5.3, r1), eve::pow_abs(5.3, r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(r0, 4), eve::pow(kyosu::abs(r0), 4), tts::prec<T>());

  using wi_t = eve::wide<unsigned int, eve::fixed<T::size()>>;
  wi_t n(eve::iota(eve::as<wi_t>()));
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(r0, n), eve::pow(kyosu::abs(r0), n), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::pow_abs over complex",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
(auto r0, auto i0, auto r1, auto i1)
{
  using T = decltype(r0);
  auto c0 = kyosu::complex(r0, i0);
  auto c1 = kyosu::complex(r1, i1);
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(c0, c1), kyosu::pow(kyosu::abs(c0), c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(r0, c1), kyosu::pow(kyosu::abs(r0), c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(c0, r1), eve::pow(kyosu::abs(c0), r1), 2e-4);
};

TTS_CASE_WITH("Check kyosu::pow_abs over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1)
{
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0, i0, j0, k0);
  auto q1 = type(r1, i1, j1, k1);
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(q0, q1), kyosu::pow(kyosu::abs(q0), q1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(r0, q1), kyosu::pow(kyosu::abs(r0), q1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::pow_abs(q0, r1), eve::pow(kyosu::abs(q0), r1), 2e-4);
};
