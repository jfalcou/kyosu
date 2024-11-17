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
  return kyosu::complex(sc.real(), sc.imag());
}

TTS_CASE_WITH( "Check behavior of exp_ipi on scalar"
        , tts::bunch<kyosu::scalar_real_types>
        , tts::generate( tts::randoms(-10, 10), tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  auto prec = (sizeof(e_t) ==  4) ? 2.0e-3 : 2.0e-5;
   using c_t = std::complex<e_t>;
  using kc_t = kyosu::complex_t<e_t>;
  auto pis = eve::pi(eve::as<e_t>());
  for(size_t i = 0; i < a0.size(); ++i)
  {
    auto e = a0[i];
    auto f = a1[i];
    TTS_RELATIVE_EQUAL(kyosu::exp_ipi(kc_t(e, f)),  cv(std::exp(c_t(-f*pis, e*pis))), prec);
  }
};

TTS_CASE_WITH( "Check behavior of exp_ipi on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::randoms(-3, 3)
                            , tts::randoms(-3, 3))
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto prec = (sizeof(eve::element_type_t<T>) ==  4)? 2.0e-3 : 2.0e-6;
  using e_t = T;
  using u_t = eve::underlying_type_t<T>;
  using ke_t = kyosu::complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  auto pis = eve::pi(eve::as<u_t>());
  auto std_exp_ipi = [&](auto x, auto y){return cv(std::exp(c_t(-y*pis, x*pis))); };
  ke_t e([&](auto i, auto){return std_exp_ipi(a0.get(i), a1.get(i)); });
  TTS_RELATIVE_EQUAL(kyosu::exp_ipi(ke_t{a0,a1}), e, prec);
};
