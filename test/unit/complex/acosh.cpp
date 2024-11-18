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

TTS_CASE_WITH( "Check behavior of acosh on scalar"
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
    auto prec = sizeof(eve::element_type_t<T>) == 8 ?  1e-6 : 1.e-3;

    TTS_RELATIVE_EQUAL(kyosu::acosh(kc_t(e, f)),  cv(std::acosh(c_t(e, f))),prec);
  }
};

TTS_CASE_WITH( "Check behavior of acosh on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = T;
  using ke_t = kyosu::complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  ke_t e([&](auto i, auto){return cv(std::acosh(c_t(a0.get(i), a1.get(i)))); });
  TTS_RELATIVE_EQUAL(kyosu::acosh(ke_t{a0,a1}), e, 1.0e-6);
};

TTS_CASE_TPL( "Check acosh lilits", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  auto tcx = kyosu::complex;
  using c_t = decltype(tcx(e_t(0)));
  using eve::as;
  const int N = 22;
  std::array<c_t, N> inputs =
    { tcx(eve::zero(as<e_t>()),eve::zero(as<e_t>())),//0*
      tcx(eve::inf(as<e_t>()),eve::zero(as<e_t>())), //1*
      tcx(eve::minf(as<e_t>()),eve::zero(as<e_t>())),//2*
      tcx(eve::nan(as<e_t>()),eve::zero(as<e_t>())), //3*
      tcx(eve::zero(as<e_t>()),eve::inf(as<e_t>())), //4*
      tcx(eve::inf(as<e_t>()),eve::inf(as<e_t>())),  //5*
      tcx(eve::minf(as<e_t>()),eve::inf(as<e_t>())), //6*
      tcx(eve::nan(as<e_t>()),eve::inf(as<e_t>())),  //7*
      tcx(eve::zero(as<e_t>()),eve::minf(as<e_t>())),//8*
      tcx(eve::inf(as<e_t>()),eve::minf(as<e_t>())), //9*
      tcx(eve::minf(as<e_t>()),eve::minf(as<e_t>())),//10*
      tcx(eve::nan(as<e_t>()),eve::minf(as<e_t>())), //11*
      tcx(eve::zero(as<e_t>()),eve::nan(as<e_t>())), //12*
      tcx(eve::inf(as<e_t>()),eve::nan(as<e_t>())),  //13*
      tcx(eve::minf(as<e_t>()),eve::nan(as<e_t>())), //14*
      tcx(eve::nan(as<e_t>()),eve::nan(as<e_t>())),  //15*
      tcx(eve::mzero(as<e_t>()),eve::zero(as<e_t>())),//16*
      tcx(eve::one(as<e_t>()),eve::inf(as<e_t>())),   //17*
      tcx(eve::one(as<e_t>()),eve::nan(as<e_t>())),   //18*
      tcx(eve::minf(as<e_t>()),eve::one(as<e_t>())),  //19*
      tcx(eve::inf(as<e_t>()),eve::one(as<e_t>())),   //20*
      tcx(eve::nan(as<e_t>()),eve::one(as<e_t>())),   //21*
    };
  std::array<c_t, N> expected =
    { tcx(eve::zero(as<e_t>()),eve::pio_2(as<e_t>())), //0*
      tcx(eve::inf(as<e_t>()),eve::zero(as<e_t>())),   //1*
      tcx(eve::inf(as<e_t>()),eve::pi(as<e_t>())),     //2*
      tcx(eve::nan(as<e_t>()),eve::nan(as<e_t>())),    //3*
      tcx(eve::inf(as<e_t>()),eve::pio_2(as<e_t>())),  //4*
      tcx(eve::inf(as<e_t>()),eve::pio_4(as<e_t>())),  //5*
      tcx(eve::inf(as<e_t>()),3*eve::pio_4(as<e_t>())),//6*
      tcx(eve::inf(as<e_t>()),eve::nan(as<e_t>())),    //7*
      tcx(eve::inf(as<e_t>()),-eve::pio_2(as<e_t>())), //8*
      tcx(eve::inf(as<e_t>()),-eve::pio_4(as<e_t>())), //9*
      tcx(eve::inf(as<e_t>()),-3*eve::pio_4(as<e_t>())),//10*
      tcx(eve::inf(as<e_t>()),eve::nan(as<e_t>())),    //11*
      tcx(eve::nan(as<e_t>()),eve::nan(as<e_t>())),    //12
      tcx(eve::inf(as<e_t>()),eve::nan(as<e_t>())),    //13*
      tcx(eve::inf(as<e_t>()),eve::nan(as<e_t>())),    //14*
      tcx(eve::nan(as<e_t>()),eve::nan(as<e_t>())),    //15*
      tcx(eve::zero(as<e_t>()),eve::pio_2(as<e_t>())), //16*
      tcx(eve::inf(as<e_t>()),eve::pio_2(as<e_t>())),  //17*
      tcx(eve::nan(as<e_t>()),eve::nan(as<e_t>())),    //18*
      tcx(eve::inf(as<e_t>()),eve::pi(as<e_t>())),     //19*
      tcx(eve::inf(as<e_t>()),eve::zero(as<e_t>())),   //20*
      tcx(eve::nan(as<e_t>()),eve::nan(as<e_t>())),    //21
    };

  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(kyosu::acosh(inputs[i]), expected[i]);
    TTS_IEEE_EQUAL(kyosu::acosh(kyosu::conj(inputs[i])), kyosu::conj(expected[i]));
  }
};
