//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_i0 over real"
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
    std::array<T, 16> reres{9.1105158918418851e+00, 1.3520681783686308e+01, 5.1996157906116176e+00, -9.3955732595530583e-01, -2.1592215730366595e+00, -1.0203442510225200e+00, 1.7928053786055054e-01, 7.9145564123437862e-01, 1.0226268793515969e+00, 9.3760847680602921e-01, 9.6892664556561592e-02, -1.8654535569280768e+00, -3.7136415921698247e+00, -1.3637442303665379e+00, 9.5845168576745756e+00, 2.3992713926047784e+01};
    std::array<T, 16> imres{-2.4327050976845694e+01, 2.8653583146189998e+00, 5.3090647906716306e+00, -3.9446445638917211e+00, 7.3190429239585508e-01, 8.0207883753193920e-01, -7.2760910016154035e-01, 1.7951149535253691e-01, 0.0000000000000000e+00, 4.9652994760912211e-01, -1.3484619725848805e+00, 1.3085405635612335e+00, 1.4854842997435447e+00, -7.0649726353849376e+00, 9.1307990856050161e+00, 5.8349474258307366e+00};
    for(size_t i=0; i < re.size(); ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i0(c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }

};


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_i0 over real"
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
  using kyosu::cyl_bessel_i0;
  auto i0c = cyl_bessel_i0(c);
  TTS_IEEE_EQUAL(i0c, cyl_bessel_i0(cm));
  TTS_IEEE_EQUAL(i0c, kyosu::conj(cyl_bessel_i0(cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
  auto z =   kyosu::complex(T(0), T(0));
  auto o =   kyosu::complex(T(1), T(0));
  TTS_IEEE_EQUAL(cyl_bessel_i0(z), o);
};
