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

template<typename T> auto cv(std::complex<T> const& sc)
{
  return kyosu::complex(sc.real(), sc.imag());
}

TTS_CASE_WITH("Check behavior of cos on scalar",
              tts::bunch<kyosu::scalar_real_types>,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  using kc_t = kyosu::complex_t<e_t>;
  for (size_t i = 0; i < a0.size(); ++i)
  {
    auto e = a0[i];
    auto f = a1[i];
    auto z = kc_t(e, f);
    TTS_EQUAL(kyosu::is_imag(z), eve::is_eqz(kyosu::real(z)));
  }
};

TTS_CASE_WITH("Check behavior of cos on wide", kyosu::simd_real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  auto z = kyosu::complex(a0, a1);
  TTS_EQUAL(kyosu::is_imag(z), eve::is_eqz(kyosu::real(z)));
};
