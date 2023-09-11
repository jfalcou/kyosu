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

TTS_CASE_WITH( "Check behavior of asinh on scalar"
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

    TTS_RELATIVE_EQUAL(kyosu::asinh(kc_t(e, f)),  cv(std::asinh(c_t(e, f))), 1.0e-4);
  }
};

TTS_CASE_WITH( "Check behavior of asinh on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::between(-10, 10)
                            , tts::between(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = T;
  using ke_t = kyosu::as_complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  ke_t e([&](auto i, auto){return cv(std::asinh(c_t(a0.get(i), a1.get(i)))); });
  TTS_RELATIVE_EQUAL(kyosu::asinh(ke_t{a0,a1}), e, 1.0e-5);
};

TTS_CASE_TPL( "Check asinh lilits", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  auto tcx = kyosu::to_complex;
  using c_t = decltype(tcx(e_t(0)));
  using eve::as;

  auto zer = eve::zero(as<T>());
  auto mzer = eve::mzero(as<T>());
  auto inf = eve::inf(as<T>());
  auto minf = eve::minf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  auto pio_2 = eve::pio_2(as<T>());
  auto pio_4 = eve::pio_4(as<T>());
  const int N = 12;
  std::array<c_t, N> inputs =
    {
      tcx(zer,zer), //0
      tcx(mzer,zer),//1
      tcx(one,inf), //2
      tcx(one,nan), //3
      tcx(inf,one), //4
      tcx(inf,inf), //5
      tcx(inf,nan), //6
      tcx(inf,one), //7
      tcx(nan,zer),//8
      tcx(nan, one), //9
      tcx(nan,inf), //10
      tcx(nan,nan),  //11
    };

  std::array<c_t, N> expected =
    {
      tcx(zer,zer), //0
      tcx(mzer,zer),//1
      tcx(inf, pio_2), //2
      tcx(nan,nan),//3
      tcx(inf,zer), //4
      tcx(inf,pio_4), //5
      tcx(inf,nan), //6
      tcx(inf,zer), //7
      tcx(nan,zer),//8
      tcx(nan, nan), //9
      tcx(minf, nan), //10
      tcx(nan,nan),  //11
    };


  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(kyosu::asinh(inputs[i]), expected[i]);
    TTS_IEEE_EQUAL(kyosu::asinh(-inputs[i]), -kyosu::asinh(inputs[i]));
    TTS_IEEE_EQUAL(kyosu::asinh(kyosu::conj(inputs[i])), kyosu::conj(expected[i]));
  }
};
