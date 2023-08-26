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

template < typename T >
auto cv(std::complex < T > const &sc)
{
  return kyosu::to_complex(sc.real(), sc.imag());
}

TTS_CASE_WITH( "Check behavior of log2 on scalar"
        , tts::bunch<kyosu::scalar_real_types>
        , tts::generate( tts::randoms(-10, 10), tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  using kc_t = kyosu::as_complex_t<e_t>;
  for(size_t i = 0; i < a0.size(); ++i)
  {
    auto e = a0[i];
    auto f = a1[i];
    auto std_log2 = [](auto x){return std::log(x)*eve::invlog_2(eve::as<e_t>()); };

    TTS_RELATIVE_EQUAL(kyosu::log2(kc_t(e, f)),  cv(std_log2(c_t(e, f))), 1.0e-6);
  }
};

TTS_CASE_WITH( "Check behavior of log2 on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::between(-10, 10)
                            , tts::between(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = T;
  using ke_t = kyosu::as_complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  auto std_log2 = [](auto x, auto y){return cv(std::log(c_t(x, y)))*eve::invlog_2(eve::as(x)); };
  ke_t e([&](auto i, auto){return std_log2(a0.get(i), a1.get(i)); });
  TTS_RELATIVE_EQUAL(kyosu::log2(ke_t{a0,a1}), e, 1.0e-6);
};
