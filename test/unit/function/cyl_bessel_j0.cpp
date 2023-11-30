//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_j0 over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  using e_t = eve::element_type_t<T>;
  if constexpr(sizeof(e_t) == 8)
  {
std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};

std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};

std::array<T, 16> reres{1.0994202526415064e+02, -6.1341983313317947e+01, -5.4746063975984825e+01, -2.4044261702680984e+01, -6.0684928660729174e+00, 2.9977058536861101e-01,1.4526323450892247e+00, 1.2105699167991699e+00, 9.7762624653829611e-01, 9.3760847680602921e-01, 5.2093811265580170e-01, -1.8812996608689940e+00, -9.1376223975139936e+00, -2.2794495422622159e+01, -3.0901357559000331e+01, 2.3691330128760768e+01};

std::array<T, 16> imres{-3.7228510471626828e+02, 1.4028409127768685e+02, -2.7081735332448620e+01, -5.8721248887491999e+00, 8.2766564391210764e+00, -4.4090348541239575e+00,1.4871447363675161e+00, -2.2151388474886807e-01, 0.0000000000000000e+00, -4.9652994760912211e-01, 1.8018640814286571e+00, -3.7356445016228856e+00, 3.7443514096768258e+00, 7.5449934565437502e+00, -5.0929189487805978e+01, 1.4801128402835954e+02};

    for(int i=0; i < 16; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j0(c), res, 1.0e-4) << i <<  " <- " << c << '\n';
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j0(re[i]), kyosu::real(kyosu::cyl_bessel_j0(kyosu::complex(re[i], e_t(0.0)))), 1.0e-4)<< re[i] << '\n';
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j0(im[i]), kyosu::real(kyosu::cyl_bessel_j0(kyosu::complex(im[i], e_t(0.0)))), 1.0e-4)<< re[i] << '\n';
    }
  }
};

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_j0 over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T a0, T a1)
{
  auto c =  kyosu::complex(a0, a1);
  auto cb=  kyosu::conj(c);
  auto cm=  -c;
  auto cr=  kyosu::complex(a0);
  auto ci=  kyosu::complex(T(0), a1);
  using kyosu::cyl_bessel_j0;
  auto j0c = cyl_bessel_j0(c);
  TTS_EQUAL(j0c, cyl_bessel_j0(cm));
  TTS_EQUAL(j0c, kyosu::conj(cyl_bessel_j0(cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
  auto z =   kyosu::complex(T(0), T(0));
  auto o =   kyosu::complex(T(1), T(0));
  TTS_IEEE_EQUAL(cyl_bessel_j0(z), o);
};
