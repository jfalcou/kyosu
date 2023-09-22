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

TTS_CASE_TPL( "Check faddeeva", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  auto tcx = kyosu::complex;
  using c_t = decltype(tcx(e_t(0)));
  using eve::as;
  const int N = 10;
  auto zer = eve::zero(as<T>());
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  auto half= eve::half(as<T>());


  std::array<c_t, N> inputs =
    {
      tcx(one,one),   //0
      tcx(half,one),  //1
      tcx(T(10.0), T(10.0)),//2
      tcx(T(65.0), zer),   //3
      tcx(T(0.01), one), //4
      tcx(T(1.0e-4), T(2.0)), //5
      tcx(T(0.785398163397448), zer), //6
      tcx(inf,zer),   //7
      tcx(inf,nan),   //8
      tcx(nan,nan)    //9
    };

  std::array<c_t, N> results =
    {
      tcx(T(3.04744205256913e-01), T(2.08218938202832e-01) ),//0
      tcx(T(3.91234021452136e-01), T(1.27202410884648e-01) ),//1
      tcx(T(2.82794674542325e-02), T(2.81384332763369e-02) ),//2
      tcx(T(0.00000000000000e+00), T(8.68086731176095e-03) ),//3
      tcx(T(4.27568139375386e-01), T(2.73204092253626e-03) ),//4
      tcx(T(2.55395675892478e-01), T(1.06796461698883e-05) ),//5
      tcx(T(5.39641485816297e-01), T(5.97805988669632e-01) ),//6
      tcx(T(0.00000000000000e+00), T(0.00000000000000e+00) ),//7
      tcx(T(0.00000000000000e+00), T(0.00000000000000e+00) ),//8
      tcx(nan, nan )                                         //9
    };
  using eve::conj;
  using kyosu::faddeeva;
  for(int i=0; i < 7; ++i)
  {
    TTS_RELATIVE_EQUAL(faddeeva(inputs[i]), results[i], 1.0e-4)  << "i " << i << " -> " << inputs[i] <<  " -> " <<faddeeva(inputs[i])<<"\n";
  }
  for(int i=7; i < N; ++i)
  {
    TTS_IEEE_EQUAL(faddeeva(inputs[i]), results[i]) << "i " << i << " -> " << inputs[i] <<  " -> " <<faddeeva(inputs[i])<<"\n";
  }
};
