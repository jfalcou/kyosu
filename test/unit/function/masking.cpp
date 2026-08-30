//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

// A false mask returns the input untouched; a true one behaves as the plain call.
TTS_CASE_WITH("Check that a conditional reaches the value-returning callables",
              kyosu::real_types,
              tts::randoms(-5, 5),
              tts::randoms(-5, 5))
<typename T>(T const& r, T const& i)
{
  auto z = kyosu::complex(r, i);

  TTS_EQUAL(kyosu::minus[false](z), z);
  TTS_EQUAL(kyosu::minus[true](z), kyosu::minus(z));

  TTS_EQUAL(kyosu::pure[false](z), z);
  TTS_EQUAL(kyosu::pure[true](z), kyosu::pure(z));

  TTS_EQUAL(kyosu::eta[false](z), z);
  TTS_EQUAL(kyosu::eta[true](z), kyosu::eta(z));
};

TTS_CASE_WITH("Check that a conditional reaches the predicates", kyosu::real_types, tts::randoms(-5, 5))
<typename T>(T const& r)
{
  using c_t = kyosu::complex_t<eve::element_type_t<T>>;

  // Values chosen so the unmasked answer is true, which is what a dropped mask hides.
  auto pure = kyosu::complex(T(0), r);
  auto real = kyosu::complex(r, T(0));
  auto ci = kyosu::cinf(kyosu::as<c_t>());

  TTS_EQUAL(kyosu::is_pure[false](pure), eve::false_(eve::as(kyosu::is_pure(pure))));
  TTS_EQUAL(kyosu::is_pure[true](pure), kyosu::is_pure(pure));

  TTS_EQUAL(kyosu::is_real[false](real), eve::false_(eve::as(kyosu::is_real(real))));
  TTS_EQUAL(kyosu::is_real[true](real), kyosu::is_real(real));

  TTS_EQUAL(kyosu::is_cinf[false](ci), eve::false_(eve::as(kyosu::is_cinf(ci))));
  TTS_EQUAL(kyosu::is_cinf[true](ci), kyosu::is_cinf(ci));

  TTS_EQUAL(kyosu::is_not_cinf[false](real), eve::false_(eve::as(kyosu::is_not_cinf(real))));
  TTS_EQUAL(kyosu::is_not_cinf[true](real), kyosu::is_not_cinf(real));
};
