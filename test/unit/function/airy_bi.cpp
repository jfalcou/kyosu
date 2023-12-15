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


    std::array<T, 16> reres{-5.7419608040318385e+07, -1.2409242416987633e+06, -2.6427659633595144e+04, -3.4216029692014837e+02, 3.0804691728218572e+01, 6.6903996777286583e+00, 1.3523669469741970e+00, 5.5870307892357129e-01, 7.5248558508731545e-01, 7.1665807338276855e-01, -7.3369695701857451e-01, -1.3293492209488911e-01, 1.1081359835209212e+00, -2.0805776844472024e+00, 3.1132412017028535e+00, -3.5952187284708805e+00};

    std::array<T, 16> imres{1.6763717755961375e+07, -1.0671669307691315e+06, 5.1770135827841987e+04, -2.7209127089468357e+03, 1.7464925781992241e+02, -1.5040759898113270e+01, 1.9670200948712224e+00, -4.4241768244532709e-01, 0.0000000000000000e+00, 6.1988929040084473e-01, -4.7545485913890873e-01, -1.2208933006131721e+00, -1.3901622231770903e+00, -1.5528897868070297e+00, -2.4569086817625085e+00, -5.1871698800009600e+00};

    for(int i=0; i < 16; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::airy_bi(c), res, 1.0e-3) << i <<  " <- " << c << '\n';
//       TTS_RELATIVE_EQUAL(kyosu::airy_bi(re[i]), kyosu::real(kyosu::airy_bi(kyosu::complex(re[i], e_t(0.0)))), 1.0e-4)<< re[i] << '\n';
//       TTS_RELATIVE_EQUAL(kyosu::airy_bi(im[i]), kyosu::real(kyosu::airy_bi(kyosu::complex(im[i], e_t(0.0)))), 1.0e-4)<< im[i] << '\n';
    }
  }
};

// TTS_CASE_WITH ( "Check kyosu::airy_bi over real"
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
//     using kyosu::airy_bi;
//     auto j0c = airy_bi(c);
//     TTS_EQUAL(j0c, kyosu::conj(airy_bi(cb))) << "c = " << c << '\n';
// //     TTS_EXPECT(eve::all(kyosu::is_real(cr)));
// //     TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
// //     auto z =   kyosu::complex(T(0), T(0));
// //     TTS_IEEE_EQUAL(airy_bi(z), kyosu::complex(airy_bi(T(0))));
//   }
// };
