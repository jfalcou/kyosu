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

TTS_CASE_WITH( "Check behavior of coth on scalar"
        , tts::bunch<kyosu::scalar_real_types>
        , tts::generate( tts::randoms(-10, 10), tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  using kc_t = kyosu::complex_t<e_t>;
  for(size_t i = 0; i < a0.size(); ++i)
  {
    auto e = a0[i];
    auto f = a1[i];
    TTS_RELATIVE_EQUAL(kyosu::coth(kc_t(e, f)),  kyosu::rec(cv(std::tanh(c_t(e, f)))), tts::prec<e_t>());
  }
};

TTS_CASE_WITH( "Check behavior of coth on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = T;
  kyosu::complex_t<e_t> a(a0, a1);
  TTS_RELATIVE_EQUAL(kyosu::coth(a),  kyosu::rec(kyosu::tanh(a)), tts::prec<e_t>());
};
