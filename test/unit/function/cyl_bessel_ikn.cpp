//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_ikn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};
    std::array<T, 16> reres2{4.0377910257037932e+00, 1.1131526087051226e+01, 5.5134372825409299e+00, 2.6219467485144321e-01, -1.4011595850044585e+00, -1.0502981158349249e+00, -4.2625656016661650e-01, -1.0399428744829654e-01, 1.1334612660978446e-02, -4.1579886943962120e-02, -5.4880819677356119e-01, -1.6836906393155004e+00, -2.3685550631515331e+00, 5.2693325633049048e-01, 9.7888465062646848e+00, 1.9610788290359256e+01};
    std::array<T, 16> imres2{-2.2907957726202113e+01, 4.9924679581718241e+00, 3.3283209314937663e+00, -3.4144016399820751e+00, 1.2319772918848950e+00, 9.4382975257347401e-02, -3.0284796812655723e-01, 8.6383554533540505e-02, 0.0000000000000000e+00, 2.4739764151330637e-01, -6.0651952574518542e-01, 2.1663109112336176e-01, 2.1226065961964480e+00, -5.9579722815610143e+00, 5.7386831869462647e+00, 9.1253114501434780e+00};
    std::array<T, 16> reres3{1.1233884194311896e+00, -8.0281804118427527e+00, -5.2105780621049034e+00, -1.2453676999005441e+00, 4.3207258423393058e-01, 5.0929522268502936e-01, 1.9675505254985781e-01, 2.1907914170279676e-02, 5.6567119054670495e-04, -4.6607480311600599e-02, -3.5568894517371541e-01, -9.3701920545934714e-01, -8.8619672060683563e-01, 1.9934200527106283e+00, 9.0326799310742185e+00, 1.4184752633683175e+01};
    std::array<T, 16> imres3{2.0180941784828413e+01, -6.6028358596344319e+00, -1.2060961901657319e+00, 2.4637722418841257e+00, -1.3449104993423109e+00, 4.0336635907674406e-01, -7.1129028123224192e-02, 1.1400169086975935e-02, 0.0000000000000000e+00, 3.6205278008366759e-02, -4.0532151701810043e-02, -4.7210545844804447e-01, 2.1546662676711930e+00, -4.2666109253585001e+00, 2.2322965885901072e+00, 1.1506879978780825e+01};


    std::vector<kyosu::complex_t<T>> is(6), ks(6);
    for (int k = 0; k < 16; ++k)
    {
      auto c = kyosu::complex(re[k], im[k]);
      kyosu::cyl_bessel_ikn(3, c, is, ks);
      int j = 0;
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i0(c), is[j], 1.0e-7) << "k " << k  << " c "<< c << '\n';
      j = 1;
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i1(c), is[j], 1.0e-7) << "k " << k  << " c "<< c << '\n';
      j = 2;
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_in(j, c), is[j], 1.0e-7) << "k " << k  << " c "<< c << '\n';
      auto ref2 =  kyosu::complex_t<T>(reres2[k], imres2[k]);
      TTS_RELATIVE_EQUAL(ref2, is[j], 1.0e-7) << "k " << k  << " c "<< c << '\n';
      j = 3;
      auto ref3 =  kyosu::complex_t<T>(reres3[k], imres3[k]);
      TTS_RELATIVE_EQUAL(ref3, is[j], 1.0e-7) << "k " << k  << " c "<< c << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_jn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};

    std::vector<kyosu::complex_t<T>> is(6), ks(6);
    for (int k = 0; k < 16; ++k)
    {
      auto c = kyosu::complex(re[k], im[k]);
      kyosu::cyl_bessel_ikn(3, c, is, ks);

      int i = 0;
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_k0(c), ks[i], 1.0e-6) << "i " << i  << " c "<< c << '\n';
      i = 1;
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_k1(c), ks[1], 1.0e-6) << "i " << i  << " c "<< c << '\n';
      for(int i=2; i < 4; ++i)
      {
        TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_kn(i, c), ks[i], 1.0e-6) << "i " << i  << " c "<< c << '\n';
      }
    }
  }
};

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_yn over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T a0, T a1)
{
  using u_t = eve::underlying_type_t<T>;
  auto z =  kyosu::complex(a0, a1);
  auto re = kyosu::complex(eve::abs(a0));
  auto zer =   kyosu::complex(T(0), T(0));
  auto minf=   kyosu::complex(eve::minf(eve::as<T>()));
  {
    auto conjz =  kyosu::conj(z);

    for(int i=0; i <10 ; ++i)
    {
      auto ynz = kyosu::cyl_bessel_yn(i, z);
      TTS_IEEE_EQUAL(ynz, kyosu::conj(kyosu::cyl_bessel_yn(i, conjz)));
      auto yre = kyosu::cyl_bessel_yn(i, kyosu::abs(re));
      TTS_EXPECT(eve::all(kyosu::is_real(yre)))<< i << " -> " << yre << '\n';
      auto yzer =  kyosu::cyl_bessel_yn(i, zer);
      TTS_IEEE_EQUAL(yzer, minf);
      TTS_IEEE_EQUAL(ynz, eve::sign_alternate(u_t(i))*kyosu::cyl_bessel_yn(-i, z)) << i << '\n';
    }
  }
};
