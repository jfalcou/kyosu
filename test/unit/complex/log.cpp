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

TTS_CASE_WITH( "Check behavior of log on scalar"
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
    TTS_RELATIVE_EQUAL(kyosu::log(kc_t(e, f)),  cv(std::log(c_t(e, f))), 1.0e-6);
  }
};

TTS_CASE_WITH( "Check behavior of log on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::between(-10, 10)
                            , tts::between(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = T;
  using ke_t = kyosu::complex_t<e_t>;
  using c_t = std::complex<eve::element_type_t<e_t>>;
  auto std_log = [](auto x, auto y){return cv(std::log(c_t(x, y))); };
  ke_t e([&](auto i, auto){return std_log(a0.get(i), a1.get(i)); });
  TTS_RELATIVE_EQUAL(kyosu::log(ke_t{a0,a1}), e, 1.0e-6);
};

TTS_CASE_TPL( "Check corner cases of log", kyosu::scalar_real_types)
  <typename T>(tts::type<T>)
{
  using c_t = kyosu::complex_t<T>;
  using eve::as;
  const int N = 14;
  auto zer = eve::zero(as<T>());
  auto mzer = eve::mzero(as<T>());
  auto inf = eve::inf(as<T>());
  auto minf = eve::minf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  auto pi = eve::pi(as<T>());
  auto pio_2 = eve::pio_2(as<T>());
  auto pio_4 = eve::pio_4(as<T>());
  std::array<c_t, N> inputs =
    {
      c_t(mzer,zer), //0
      c_t(zer,zer),  //1
      c_t(one,inf),  //2
      c_t(one,nan),  //3
      c_t(minf,one), //4
      c_t(minf,zer), //5
      c_t(inf,one),  //6
      c_t(inf,zer),  //7
      c_t(inf,inf),  //8
      c_t(inf, nan), //9
      c_t(minf,nan), //10
      c_t(nan,one),  //11
      c_t(nan,inf),  //12
      c_t(nan,nan)   //13
    };

  std::array<c_t, N> results =
    {
      c_t(minf,pi),   //0
      c_t(minf,zer),  //1
      c_t(inf,pio_2), //2
      c_t(nan,nan),   //3
      c_t(inf,pi),    //4
      c_t(inf,pi),    //5
      c_t(inf,zer),   //6
      c_t(inf,zer),   //7
      c_t(inf,pio_4), //8
      c_t(inf, nan),  //9
      c_t(inf,nan),   //10
      c_t(nan,nan),   //11
      c_t(inf,nan),   //12
      c_t(nan,nan)    //13
    };

  using kyosu::conj;
  using kyosu::log;
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(log(inputs[i]), results[i]) << "i " << i << " -> " << inputs[i] << "\n";
    TTS_IEEE_EQUAL(log(conj(inputs[i])), conj(log(inputs[i])));
  }

  using wc_t = eve::wide<c_t, eve::fixed<8>>;
  wc_t wci0([inputs](auto i, auto){return inputs[i]; });
  wc_t wco0([results](auto i, auto){return results[i]; });
  wc_t wci1([inputs](auto i, auto c){return inputs[c-i-1]; });
  wc_t wco1([results](auto i, auto c){return results[c-i-1]; });
  TTS_IEEE_EQUAL(log(wci0), wco0);
  TTS_IEEE_EQUAL(log(wci1), wco1);

};
