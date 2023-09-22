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

TTS_CASE_WITH( "Check behavior of sqrt on scalar"
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

    TTS_RELATIVE_EQUAL(kyosu::sqrt(kc_t(e, f)),  cv(std::sqrt(c_t(e, f))), 1.0e-6);
  }
};

TTS_CASE_WITH( "Check behavior of sqrt on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::between(-10, 10)
                            , tts::between(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = T;
  using ke_t = kyosu::complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  ke_t e([&](auto i, auto){return cv(std::sqrt(c_t(a0.get(i), a1.get(i)))); });
  TTS_RELATIVE_EQUAL(kyosu::sqrt(ke_t{a0,a1}), e, 1.0e-6);
};

TTS_CASE_TPL( "Check corner cases of sqrt", kyosu::scalar_real_types)
  <typename T>(tts::type<T>)
{
  using c_t = kyosu::complex_t<T>;
  using eve::as;
  const int N = 14;
  auto zer = eve::zero(as<T>());
  auto mzer = eve::mzero(as<T>());
  auto inf = eve::inf(as<T>());
  auto minf = eve::minf(as<T>());
  auto mone = eve::mone(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  std::array<c_t, N> inputs =
    {
      c_t(zer,zer), //0
      c_t(mzer,zer),//1
      c_t(one,inf), //2
      c_t(mone,inf),//3
      c_t(nan,inf), //4
      c_t(one,nan), //5
      c_t(minf,one), //6
      c_t(inf,one), //7
      c_t(minf,-nan),//8
      c_t(inf,nan), //9
      c_t(nan,one), //10
      c_t(nan,nan),  //11
      c_t(T(4), zer),  //12
      c_t(nan,zer)  //13
    };

  std::array<c_t, N> results =
    {
      c_t(zer,zer), //0
      c_t(zer,zer),//1
      c_t(inf,inf), //2
      c_t(inf,inf),//3
      c_t(inf,inf), //4
      c_t(nan,nan), //5
      c_t(zer,inf), //6
      c_t(inf,zer), //7
      c_t(nan,minf),//8
      c_t(inf,nan), //9
      c_t(nan,nan), //10
      c_t(nan,nan),  //11
      c_t(T(2), zer),  //12
      c_t(nan,nan)  //13
    };

  using kyosu::conj;
  using kyosu::sqrt;
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(sqrt(inputs[i]), results[i]);
//    TTS_IEEE_EQUAL(sqrt(conj(inputs[i])), conj(sqrt(inputs[i])));
  }
};
