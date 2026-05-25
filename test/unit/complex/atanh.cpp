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

TTS_CASE_WITH("Check behavior of atanh on scalar",
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

    TTS_RELATIVE_EQUAL(kyosu::atanh(kc_t(e, f)), cv(std::atanh(c_t(e, f))), tts::prec<T>());
  }
};

TTS_CASE_WITH("Check behavior of atanh on wide", kyosu::simd_real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  using e_t = T;
  using ke_t = kyosu::complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  ke_t e([&](auto i, auto) { return cv(std::atanh(c_t(a0.get(i), a1.get(i)))); });
  TTS_RELATIVE_EQUAL(kyosu::atanh(ke_t{a0, a1}), e, tts::prec<T>());
};

auto sc(auto ec)
{
  return std::complex(kyosu::real(ec), kyosu::imag(ec));
}

TTS_CASE_TPL("Check corner casesof eve::atanh", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  if constexpr (spy::operating_system != spy::macos_)
  {
    using e_t = T;
    auto tcx = kyosu::complex;
    using c_t = decltype(tcx(e_t(0)));
    using eve::as;
    int const N = 11;
    std::array<c_t, N> inputs = {
      c_t(eve::zero(as<e_t>()), eve::zero(as<e_t>())), // 0
      c_t(eve::zero(as<e_t>()), eve::nan(as<e_t>())),  // 1
      c_t(eve::one(as<e_t>()), eve::zero(as<e_t>())),  // 2
      c_t(eve::one(as<e_t>()), eve::inf(as<e_t>())),   // 3
      c_t(eve::one(as<e_t>()), eve::nan(as<e_t>())),   // 4
      c_t(eve::inf(as<e_t>()), eve::one(as<e_t>())),   // 5
      c_t(eve::inf(as<e_t>()), eve::inf(as<e_t>())),   // 6
      c_t(eve::inf(as<e_t>()), eve::nan(as<e_t>())),   // 7
      c_t(eve::nan(as<e_t>()), eve::one(as<e_t>())),   // 8
      c_t(eve::nan(as<e_t>()), eve::inf(as<e_t>())),   // 9
      c_t(eve::nan(as<e_t>()), eve::nan(as<e_t>())),   // 10
    };

    std::array<c_t, N> results = {
      c_t(eve::zero(as<e_t>()), eve::zero(as<e_t>())),  // 0
      c_t(eve::zero(as<e_t>()), eve::nan(as<e_t>())),   // 1
      c_t(eve::inf(as<e_t>()), eve::zero(as<e_t>())),   // 2
      c_t(eve::zero(as<e_t>()), eve::pio_2(as<e_t>())), // 3
      c_t(eve::nan(as<e_t>()), eve::nan(as<e_t>())),    // 4
      c_t(eve::zero(as<e_t>()), eve::pio_2(as<e_t>())), // 5
      c_t(eve::zero(as<e_t>()), eve::pio_2(as<e_t>())), // 6
      c_t(eve::zero(as<e_t>()), eve::nan(as<e_t>())),   // 7
      c_t(eve::nan(as<e_t>()), eve::nan(as<e_t>())),    // 8
      c_t(eve::zero(as<e_t>()), eve::pio_2(as<e_t>())), // 5
      c_t(eve::nan(as<e_t>()), eve::nan(as<e_t>())),    // 10
    };

    for (int i = 0; i < N; ++i)
    {
      std::cout << i << std::endl;
      //       TTS_IEEE_EQUAL(kyosu::atanh(inputs[i]), results[i]);
      //       TTS_IEEE_EQUAL(kyosu::atanh(-inputs[i]), -results[i]);
      //       TTS_IEEE_EQUAL(kyosu::atanh(kyosu::conj(inputs[i])), kyosu::conj(results[i]));
      //        std::cout << "input    " << inputs[i] << std::endl;
      //      std::cout << "pedantic " << kyosu::atanh[eve::pedantic](c_t(inputs[i])) << std::endl;
      //      std::cout << "regular  " << kyosu::atanh               (c_t(inputs[i])) << std::endl;
      //      std::cout << "std      " << cv(std::atanh(sc(inputs[i]))) << std::endl;
      //        std::cout << "expected " << results[i] << std::endl;
      using eve::pedantic;
      TTS_IEEE_EQUAL(kyosu::atanh[pedantic](inputs[i]), results[i]);
      TTS_IEEE_EQUAL(kyosu::atanh[pedantic](-inputs[i]), -results[i]);
      TTS_IEEE_EQUAL(kyosu::atanh[pedantic](kyosu::conj(inputs[i])), kyosu::conj(results[i]));
    }
    //    std::cout << kyosu::atanh[eve::pedantic](c_t(-100.0, 100.0)) << std::endl;
  }
  else TTS_PASS("no test for macosx: atanh corner cases are almost all false according C99");
};
