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

TTS_CASE_WITH( "Check behavior of atanh on scalar"
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

    TTS_RELATIVE_EQUAL(kyosu::atanh(kc_t(e, f)),  cv(std::atanh(c_t(e, f))), 1.0e-4);
  }
};

TTS_CASE_WITH( "Check behavior of atanh on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::between(-10, 10)
                            , tts::between(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = T;
  using ke_t = kyosu::as_complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  ke_t e([&](auto i, auto){return cv(std::atanh(c_t(a0.get(i), a1.get(i)))); });
  TTS_RELATIVE_EQUAL(kyosu::atanh(ke_t{a0,a1}), e, 1.0e-6);
};


auto sc( auto  ec)
{
  return std::complex(kyosu::real(ec), kyosu::imag(ec));
}

TTS_CASE_TPL( "Check corner casesof eve::atanh", kyosu::scalar_real_types)
  <typename T>(tts::type<T>)
{
  if constexpr(spy::stdlib != spy::libcpp_)
  {
    using e_t = T;
    auto tcx = kyosu::to_complex;
    using c_t = decltype(tcx(e_t(0)));
    using eve::as;
    const int N = 16;
    std::array<c_t, N> inputs =
      { c_t(eve::zero(as<e_t>()),eve::zero(as<e_t>())),//0
        c_t(eve::inf(as<e_t>()),eve::zero(as<e_t>())), //1
        c_t(eve::minf(as<e_t>()),eve::zero(as<e_t>())),//2
        c_t(eve::nan(as<e_t>()),eve::zero(as<e_t>())), //3
        c_t(eve::zero(as<e_t>()),eve::inf(as<e_t>())), //4
        c_t(eve::inf(as<e_t>()),eve::inf(as<e_t>())),  //5
        c_t(eve::minf(as<e_t>()),eve::inf(as<e_t>())), //6
        c_t(eve::nan(as<e_t>()),eve::inf(as<e_t>())),  //7
        c_t(eve::zero(as<e_t>()),eve::minf(as<e_t>())),//8--
        c_t(eve::inf(as<e_t>()),eve::minf(as<e_t>())), //9
        c_t(eve::minf(as<e_t>()),eve::minf(as<e_t>())),//10
        c_t(eve::nan(as<e_t>()),eve::minf(as<e_t>())), //11
        c_t(eve::zero(as<e_t>()),eve::nan(as<e_t>())), //12
        c_t(eve::inf(as<e_t>()),eve::nan(as<e_t>())),  //13
        c_t(eve::minf(as<e_t>()),eve::nan(as<e_t>())), //14
        c_t(eve::nan(as<e_t>()),eve::nan(as<e_t>())),  //15
      };

    for(int i=0; i < N; ++i)
    {
      if((i != 2 && i != 1)){
        // this curious test corresponds to the fact that neither std::atanh nor std::atanh are correct for inputs (0, inf) or (0, -inf)
        // peculiarly they contredict the C99 specification that atanh is odd
        // atanh should behave "the same as C99 function catanh, defined in subclause 7.3.6.3 and G.5.2.3."
        // the if clause has to be removed if/when libc++ will be corrected
        TTS_IEEE_EQUAL(kyosu::atanh(inputs[i]), cv(std::atanh(sc(inputs[i]))));
        TTS_IEEE_EQUAL(kyosu::atanh(-inputs[i]), cv(std::atanh(sc(-inputs[i]))));
      }
    }
  }
  else
    TTS_PASS("no test for clang standard lib atanh corner cases are almost all false according C99");
};
