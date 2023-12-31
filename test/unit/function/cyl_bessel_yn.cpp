//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_yn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};
    std::array<T, 16> reres{1.3958417197710105e+02, -8.6883096628337686e+00, -2.3631195977314693e+01, -1.2352010359832823e+01, -4.0302717962534498e+00, -8.5196208880386270e-01, -3.3849774094703877e-01, -3.4588704199830058e+00, -1.9077481501430970e+02, 8.6563240968334842e-01, -2.6730571856144153e-01, -1.4969677000121437e+00, -4.5914157362414194e+00, -9.2308592187965992e+00, -5.4336540845736305e+00, 4.6394923953405495e+01};
    std::array<T, 16> imres{-2.1919616943417924e+02, 9.5961003073477983e+01, -2.6247460558083521e+01, 2.7347064607671414e+00, 1.5534314105179585e+00, -1.0675005055809359e+00, 4.0136093823646224e-01, 1.1898693688647326e+00, 0.0000000000000000e+00, 1.4716089522370916e+00, 2.7277617257286835e-02, -3.5557851239194410e-01, -1.0774854268796867e+00, 9.5546455890845188e+00, -3.5934122187452630e+01, 8.6383214741966171e+01};
    for(int i=0; i < 16; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_yn(3, c), res, 1.0e-6) << i <<  " <- " << c << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_yn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};
    using z_t = kyosu::complex_t<T>;
    int n = 6;
    std::vector<z_t> ys(n+1);
    for(int i=0; i < 16; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      kyosu::cyl_bessel_yn(n, c, ys);

      for(int k=0; k <= n; ++k)
      {
        TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_yn(k, c), ys[k], 1.0e-7) << k <<  " <- " << c << '\n';
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
