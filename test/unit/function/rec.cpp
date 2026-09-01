//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <complex>

TTS_CASE_WITH("Check kyosu::rec over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_ULP_EQUAL(kyosu::rec(data), eve::rec(data), 0.5);
};

TTS_CASE_WITH("Check kyosu::rec over quaternion",
              kyosu::simd_real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r, T i, T j, T k)
{
  auto o = eve::one(eve::as(eve::underlying_type_t<T>()));
  using ke_t = kyosu::quaternion_t<T>;
  auto q = ke_t(r, i, j, k);
  TTS_RELATIVE_EQUAL(kyosu::rec(q), o / q, tts::prec<T>());
  auto q0 = ke_t(r);
  TTS_RELATIVE_EQUAL(kyosu::rec(q0), ke_t(o / r), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::rec over complex", kyosu::simd_real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T r, T i)
{
  using kyosu::rec;
  auto o = eve::one(eve::as(eve::underlying_type_t<T>()));
  using ce_t = kyosu::complex_t<T>;
  auto q = ce_t(r, i);
  TTS_RELATIVE_EQUAL(kyosu::rec(q), o / q, tts::prec<T>());
  auto a = ce_t(T(4), T(0.0));
  TTS_EXPECT(eve::all(eve::is_eqpz(kyosu::imag(rec(a)))));
  TTS_EXPECT(eve::all(eve::is_eqmz(kyosu::imag(rec(-a)))));
  auto b = ce_t(T(-4), T(0.0));
  TTS_EXPECT(eve::all(eve::is_eqmz(kyosu::imag(rec(b)))));
  TTS_EXPECT(eve::all(eve::is_eqpz(kyosu::imag(rec(-b)))));

  TTS_RELATIVE_EQUAL(kyosu::rec[kyosu::pedantic](q), o / q, tts::prec<T>());

  TTS_EQUAL(eve::signnz(kyosu::imag(rec[kyosu::pedantic](a))), eve::signnz(kyosu::imag(rec(a))));
  TTS_EQUAL(eve::signnz(kyosu::imag(rec[kyosu::pedantic](-a))), eve::signnz(kyosu::imag(rec(-a))));
  TTS_EQUAL(eve::signnz(kyosu::imag(rec[kyosu::pedantic](b))), eve::signnz(kyosu::imag(rec(b))));
  TTS_EQUAL(eve::signnz(kyosu::imag(rec[kyosu::pedantic](-b))), eve::signnz(kyosu::imag(rec(-b))));

  auto c = ce_t(T(0.0), T(0.0));
  TTS_IEEE_EQUAL(kyosu::rec(c), kyosu::inf(eve::as(c)));
  TTS_IEEE_EQUAL(kyosu::rec[kyosu::pedantic](c), kyosu::mulmi(kyosu::cinf(eve::as(c))));
};
