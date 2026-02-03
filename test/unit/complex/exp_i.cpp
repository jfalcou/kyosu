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

TTS_CASE_WITH("Check behavior of exp_i on scalar",
              tts::bunch<kyosu::scalar_real_types>,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  using kc_t = kyosu::complex_t<e_t>;
  for (size_t i = 0; i < a0.size(); ++i)
  {
    auto e = a0[i];
    auto f = a1[i];
    TTS_RELATIVE_EQUAL(kyosu::exp_i(kc_t(e, f)), cv(std::exp(c_t(-f, e))), tts::prec<T>());
  }
};

TTS_CASE_WITH("Check behavior of exp_i on wide", kyosu::simd_real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  using e_t = T;
  using ke_t = kyosu::complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  auto std_exp_i = [](auto x, auto y) { return cv(std::exp(c_t(-y, x))); };
  ke_t e([&](auto i, auto) { return std_exp_i(a0.get(i), a1.get(i)); });
  TTS_RELATIVE_EQUAL(kyosu::exp_i(ke_t{a0, a1}), e, tts::prec<T>());
};
