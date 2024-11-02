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

TTS_CASE_WITH( "Check behavior of asin on scalar"
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

    TTS_RELATIVE_EQUAL(kyosu::asin(kc_t(e, f)),  cv(std::asin(c_t(e, f))), 1.0e-4);
  }
};

TTS_CASE_WITH( "Check behavior of asin on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = T;
  using ke_t = kyosu::complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  ke_t e([&](auto i, auto){return cv(std::asin(c_t(a0.get(i), a1.get(i)))); });
  TTS_RELATIVE_EQUAL(kyosu::asin(ke_t{a0,a1}), e, 1.0e-3);
};


auto sc( auto  ec)
{
  return std::complex(kyosu::real(ec), kyosu::imag(ec));
}

TTS_CASE_TPL( "Check asin lilits", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  auto tcx = kyosu::complex;
  using c_t = decltype(tcx(e_t(0)));
  using eve::as;
  const int N = 12;
  auto zer = eve::zero(as<T>());
  auto mzer = eve::mzero(as<T>());
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());

  std::array<c_t, N> inputs =
    {
      c_t(zer,zer), //0
      c_t(mzer,zer),//1
      c_t(one,inf), //2
      c_t(one,nan), //3
      c_t(inf,one), //4
      c_t(inf,inf), //5
      c_t(inf,nan), //6
      c_t(inf,one), //7
      c_t(nan,zer), //8
      c_t(nan, one),//9
      c_t(nan,inf), //10
      c_t(nan,nan), //11
    };

  using kyosu::conj;
  using kyosu::asin;

  auto test_asin = [](auto z){ return cv(std::asin(sc(z))); };
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(asin(inputs[i]), test_asin(inputs[i]));
    TTS_IEEE_EQUAL(asin(-inputs[i]), -asin(inputs[i]));
    TTS_IEEE_EQUAL(asin(conj(inputs[i])), conj(asin(inputs[i])));
  }
};

TTS_CASE_TPL( "Check corner casesof eve::asin", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  auto tcx = kyosu::complex;
  using c_t = decltype(tcx(e_t(0)));
  using eve::as;
  const int N = 12;
  auto zer = eve::zero(as<T>());
  auto mzer = eve::mzero(as<T>());
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  std::array<c_t, N> inputs =
    {
      c_t(zer,zer), //0
      c_t(mzer,zer),//1
      c_t(one,inf), //2
      c_t(one,nan), //3
      c_t(inf,one), //4
      c_t(inf,inf), //5
      c_t(inf,nan), //6
      c_t(inf,one), //7
      c_t(nan,zer), //8
      c_t(nan, one),//9
      c_t(nan,inf), //10
      c_t(nan,nan), //11
    };
  using kyosu::conj;
  using kyosu::asin;

  auto test_asin = [](auto z){ return cv(std::asin(sc(z))); };
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(asin(inputs[i]), test_asin(inputs[i]));
    TTS_IEEE_EQUAL(asin(-inputs[i]), -asin(inputs[i]));
    TTS_IEEE_EQUAL(asin(conj(inputs[i])), conj(asin(inputs[i])));
  }
};
