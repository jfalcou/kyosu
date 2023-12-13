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
    std::array<T, 16> re{
      -5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00
        , -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01
        , 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00
        , 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00
        };
    std::array<T, 16> im{
      8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00
        , 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00
        , -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00
        , -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00
        };
    std::array<T, 16> reres{
      1.6763717755962929e+07, 1.0671669307692060e+06, 5.1770135828865488e+04, 2.7209127311234188e+03
        , 1.7464957947925365e+02, 1.5043848907202149e+01, 1.9864751505771967e+00, 5.2597973488369920e-01
        , 2.7880648195500490e-01, 6.0458308371838042e-02, -1.0036228447036250e-01, 2.4722152686112525e-02
        , 8.1141306614663667e-03, -1.1116711994387154e-02, 6.2362124668067535e-03, -1.1845517847442273e-03
        };
        std::array<T, 16> imres{
          5.7419608040318936e+07, -1.2409242416987466e+06, 2.6427659633621028e+04, -3.4216030566322274e+02
            , -3.0804431341868103e+01, 6.6862293791164378e+00, -1.3118365573923054e+00, 3.2173225694177510e-01
            , 0.0000000000000000e+00, -1.5188956587718155e-01, 2.1867029634299019e-02, 6.0030132776007987e-02
            , 3.9632838829414818e-02, 2.2033585182583651e-02, 1.3313384345125566e-02, 8.4631437627202440e-03};


    for(int i=0; i < 16; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      std::cout << "i " << i << " c " << c << " arg(c) " << kyosu::arg(c) << " sqrt(c) "<< kyosu::sqrt(c) << std::endl;
      TTS_RELATIVE_EQUAL(kyosu::airy_ai(c), res, 1.0e-4) << i <<  " <- " << c << '\n';
//       TTS_RELATIVE_EQUAL(kyosu::airy_ai(re[i]), kyosu::real(kyosu::airy_ai(kyosu::complex(re[i], e_t(0.0)))), 1.0e-4)<< re[i] << '\n';
//       TTS_RELATIVE_EQUAL(kyosu::airy_ai(im[i]), kyosu::real(kyosu::airy_ai(kyosu::complex(im[i], e_t(0.0)))), 1.0e-4)<< re[i] << '\n';
    }
  }
};

// TTS_CASE_WITH ( "Check kyosu::airy_ai over real"
//               , kyosu::real_types
//               , tts::generate(tts::randoms(-10,10),
//                               tts::randoms(-10,10)
//                              )
//               )
// <typename T>(T a0, T a1)
// {
//   using u_t = eve::underlying_type_t<T>;
//   if constexpr(sizeof(u_t) == 8)
//   {
//     auto c =  kyosu::complex(a0, a1);
//     auto cb=  kyosu::conj(c);
// //     auto cr=  kyosu::complex(a0);
// //     auto ci=  kyosu::complex(T(0), a1);
//     using kyosu::airy_ai;
//     auto j0c = airy_ai(c);
//     TTS_EQUAL(j0c, kyosu::conj(airy_ai(cb))) << "c = " << c << '\n';
// //     TTS_EXPECT(eve::all(kyosu::is_real(cr)));
// //     TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
// //     auto z =   kyosu::complex(T(0), T(0));
// //     TTS_IEEE_EQUAL(airy_ai(z), kyosu::complex(airy_ai(T(0))));
//   }
// };
