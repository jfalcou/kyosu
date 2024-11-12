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

TTS_CASE_WITH( "Check behavior of exp on scalar"
        , tts::bunch<kyosu::scalar_real_types>
        , tts::generate( tts::randoms(-10, 10), tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  auto prec = (sizeof(e_t) ==  4) ? 1.0e-3 : 1.0e-6;
  using c_t = std::complex<e_t>;
  using kc_t = kyosu::complex_t<e_t>;
  for(size_t i = 0; i < a0.size(); ++i)
  {
    auto e = a0[i];
    auto f = a1[i];
    TTS_RELATIVE_EQUAL(kyosu::expm1(kc_t(e, f)),  kyosu::dec(cv(std::exp(c_t(e, f)))), prec);
  }
};

TTS_CASE_WITH( "Check behavior of exp on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = T;
  using ke_t = kyosu::complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  auto std_expm1 = [](auto x, auto y){return kyosu::dec(cv(std::exp(c_t(x, y)))); };
  ke_t e([&](auto i, auto){return std_expm1(a0.get(i), a1.get(i)); });
  TTS_RELATIVE_EQUAL(kyosu::expm1(ke_t{a0,a1}), e, 4.0e-3);
};

TTS_CASE_TPL( "Check corner cases of exp", kyosu::scalar_real_types)
  <typename T>(tts::type<T>)
{
  using c_t = kyosu::complex_t<T>;
  using eve::as;
  const int N = 12;
  auto zer = eve::zero(as<T>());
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  std::array<c_t, N> inputs =
    {
      c_t(zer,zer), //0
      c_t(zer,inf), //1
      c_t(zer,nan), //2
      c_t(one,inf), //3
      c_t(one,nan), //4
      c_t(inf,zer), //5
      c_t(inf,one), //6
      c_t(inf,inf), //7
      c_t(inf,nan), //8
      c_t(nan,zer), //9
      c_t(nan,one), //10
      c_t(nan,nan), //11
    };

  std::array<c_t, N> results =
    {
      c_t(zer,zer), //0
      c_t(nan,nan), //1
      c_t(nan,nan), //2
      c_t(nan,nan), //3
      c_t(nan,nan), //4
      c_t(inf,zer), //5
      inf*c_t(eve::cos(one), eve::sin(one))-one, //6
      c_t(inf,nan),//7
      c_t(inf,nan), //8
      c_t(nan,zer), //9
      c_t(nan,nan), //10
      c_t(nan,nan)  //11
    };
  using kyosu::conj;
  using kyosu::exp;
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(kyosu::expm1(inputs[i]), results[i]) << "i " << i << '\n';
    TTS_IEEE_EQUAL(kyosu::expm1(kyosu::conj(inputs[i])), kyosu::conj(kyosu::expm1(inputs[i])));
  }
  auto e = eve::euler(as<T>());
  TTS_RELATIVE_EQUAL(kyosu::expm1(c_t{one, zer}),   (c_t{e-one, zer}), 1.0e-7);
  TTS_RELATIVE_EQUAL(kyosu::expm1(c_t{zer, zer}),   (c_t{zer, zer}), 1.0e-7);
};
