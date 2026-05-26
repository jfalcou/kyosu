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

TTS_CASE_WITH("Check behavior of exp on scalar",
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
    TTS_RELATIVE_EQUAL(kyosu::exp(kc_t(e, f)), cv(std::exp(c_t(e, f))), tts::prec<e_t>());
  }
};

TTS_CASE_WITH("Check behavior of exp on wide", kyosu::simd_real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  using e_t = T;
  using ke_t = kyosu::complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  auto std_exp = [](auto x, auto y) { return cv(std::exp(c_t(x, y))); };
  ke_t e([&](auto i, auto) { return std_exp(a0.get(i), a1.get(i)); });
  TTS_RELATIVE_EQUAL(kyosu::exp(ke_t{a0, a1}), e, tts::prec<T>());
};

TTS_CASE_TPL("Check corner cases of exp", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using c_t = kyosu::complex_t<T>;
  using eve::as;
  int const N = 13;
  auto zer = eve::zero(as<T>());
  auto inf = eve::inf(as<T>());
  auto minf = eve::minf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  auto ei = kyosu::exp_i(one);
  std::array<c_t, N> inputs = {
    c_t(zer, zer),  // 0*
    c_t(one, inf),  // 1*
    c_t(one, nan),  // 2*
    c_t(inf, zer),  // 3*
    c_t(minf, one), // 4*
    c_t(inf, one),  // 5*
    c_t(minf, inf), // 6**
    c_t(inf, inf),  // 7**
    c_t(minf, nan), // 8*
    c_t(inf, nan),  // 9*
    c_t(nan, zer),  // 10*
    c_t(nan, one),  // 11*
    c_t(nan, nan)   // 12*
  };

  std::array<c_t, N> results = {
    c_t(one, zer), // 0*
    c_t(nan, nan), // 1*
    c_t(nan, nan), // 2*
    c_t(inf, zer), // 3*
    zer * ei,      // 4*
    inf * ei,      // 5*
    c_t(zer, zer), // 6*
    c_t(inf, nan), // 7*
    c_t(zer, zer), // 8*
    c_t(inf, nan), // 9*
    c_t(nan, zer), // 10*
    c_t(nan, nan), // 11*
    c_t(nan, nan)  // 12*
  };

  std::array<c_t, N> raw_results = {
    c_t(one, zer), // 0*
    c_t(nan, nan), // 1*
    c_t(nan, nan), // 2*
    c_t(inf, nan), // 3*
    zer * ei,      // 4*
    inf * ei,      // 5*
    c_t(nan, nan), // 6*
    c_t(nan, nan), // 7*
    c_t(nan, nan), // 8*
    c_t(nan, nan), // 9*
    c_t(nan, nan), // 10*
    c_t(nan, nan), // 11*
    c_t(nan, nan)  // 12*
  };

  using kyosu::conj;
  using kyosu::exp;
  for (int i = 0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(exp[eve::raw](inputs[i]), raw_results[i]);
    TTS_IEEE_EQUAL(exp(inputs[i]), results[i]);
    TTS_IEEE_EQUAL(exp(conj(inputs[i])), conj(exp(inputs[i])));
  }
  auto e = eve::euler(as<T>());
  TTS_RELATIVE_EQUAL(kyosu::exp(c_t{one, zer}), (c_t{e, zer}), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::exp(c_t{zer, zer}), (c_t{one, zer}), tts::prec<T>());
};
