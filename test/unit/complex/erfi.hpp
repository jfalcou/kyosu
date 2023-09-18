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

TTS_CASE_TPL( "Check corner cases of erfcx", kyosu::real_types)
  <typename T>(tts::type<T>)
{
  using e_t = T;
  using c_t = decltype(kyosu::to_complex(e_t(0)));
  using eve::as;
  const int N = 9;
 auto zer = eve::zero(as<T>());
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  auto half= eve::half(as<T>());
  auto tcx = [](auto r, auto i){return kyosu::to_complex(T(r), T(i));};


  std::array<c_t, N> z =
    {
      tcx(one,one),   //0
      tcx(half,one),  //1
      tcx(10, 10),    //2
      tcx(65, zer),   //3
      tcx(0.01, one), //4
      tcx(1.0e-4, 2), //5
      tcx(0.785398163397448, zer), //6
      tcx(inf,zer),   //7
      tcx(nan,nan)    //8
    };

  std::array<c_t, N> w =
    {
      tcx(3.04744205256913e-01, -2.08218938202832e-01 ), //0
      tcx(3.54900332867578e-01, -3.42871719131101e-01 ), //1
      tcx(2.82794674542325e-02, -2.81384332763369e-02 ), //2
      tcx(eve::erfcx(T(65)), zer), //tcx(8.67881291138928e-03, +0.00000000000000e+00 ), //3
      tcx(3.68702417397766e-01, -5.99851994495788e-01 ), //4
      tcx(1.83388101767463e-02, -3.40018889576381e-01 ), //5
      tcx(4.94195834537586e-01, +0.00000000000000e+00 ), //6
      tcx(eve::erfcx(inf), zer), //tcx(0.00000000000000e+00, +0.00000000000000e+00 ), //7
      tcx(nan                ,  nan                   )  //8
    };
  using kyosu::erfcx;
  using kyosu::conj;
  double ulps = 2000;
  for(int i=0; i < N; ++i)
  {
    if (i < 21 || i > 34)
    {
      auto [er, ei] = erfcx(z[i]);
      auto [wr, wi] = w[i];

      TTS_ULP_EQUAL(er, wr, ulps) << "i " << i << " -> " << z[i] <<  " -> " <<erfcx(z[i]) <<  " -> " <<w[i] <<"\n";
      TTS_ULP_EQUAL(ei, wi, ulps) << "i " << i << " -> " << z[i] <<  " -> " <<erfcx(z[i]) <<  " -> " <<w[i] <<'\n';
    }
  }
};

TTS_CASE_WITH( "Check behavior of erfcx on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::randoms(-10.0, 10.0)
                            , tts::randoms(-10.0, 10.0))
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = kyosu::to_complex(a0, a1);
  auto ez = kyosu::erfcx(z);
  for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
  {
    TTS_RELATIVE_EQUAL(ez.get(i), kyosu::erfcx(z.get(i)), 1.0e-4);
  }
};
