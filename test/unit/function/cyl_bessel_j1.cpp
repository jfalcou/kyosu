//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_j1 over real"
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

    std::array<T, 16> reres{3.5261736422778330e+02, 1.3532335888033961e+02, 2.7699759768911626e+01, -4.2643934472523917e+00, -7.1432412137305779e+00, -3.8913705040901281e+00, -1.3789048590911068e+00, -2.7460991266929441e-01, 1.4831881627310392e-01, 6.1416033492290367e-01, 1.6523034064338877e+00, 3.2031348760663070e+00, 2.8517423787225713e+00, -8.2409938315074083e+00, -4.9501671082782835e+01, -1.4029160913677495e+02};

    std::array<T, 16> imres{1.1634998451985952e+02, 5.3381323679436136e+01, -5.0389099238087169e+01, 2.2598019114443215e+01, -6.0329512052803871e+00, 1.3571314467505077e-01, 8.9917883078392957e-01, -5.3118857437264089e-01, 0.0000000000000000e+00, 3.6502802882708785e-01, -1.2914522061506584e-01, -2.0402821881931246e+00, 8.6660326577272038e+00, -2.0946005568638384e+01, 2.7077615612492497e+01, 2.7914572954983136e+01};

    for(int i=0; i < 16; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j1(c), res, 1.0e-7) << i <<  " <- " << c << '\n';
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j1(re[i]), kyosu::real(kyosu::cyl_bessel_j1(kyosu::complex(re[i], e_t(0.0)))), 1.0e-4)<< re[i] << '\n';
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j1(im[i]), kyosu::real(kyosu::cyl_bessel_j1(kyosu::complex(im[i], e_t(0.0)))), 1.0e-4)<< re[i] << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_j1 over real"
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
  using kyosu::cyl_bessel_j1;
  auto j1c = cyl_bessel_j1(c);
  TTS_IEEE_EQUAL(j1c, -cyl_bessel_j1(cm));
  TTS_IEEE_EQUAL(j1c, kyosu::conj(cyl_bessel_j1(cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
  auto z =   kyosu::complex(T(0), T(0));
  TTS_IEEE_EQUAL(cyl_bessel_j1(z), z);
};
