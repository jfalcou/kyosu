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
    std::array<T, 16> reres{-6.9868644506618311e-05, 2.7064676972685243e+02, 3.6886164009504170e-04, -8.5309491355821621e+00, 6.7926396008222457e-03, -7.7947066285489113e+00, -1.3037972953166450e-02, -2.6465006046269030e-01, 1.4831881627310406e-01, -1.5640669069980788e-02, 3.2658114168417036e+00, 2.0448522418679817e-02, 5.6969763924510062e+00, 1.1844646693963893e-03, -9.9003239995999664e+01, -1.8815491376888570e-04};
    std::array<T, 16> imres{-5.5439750416853029e-05, 1.0676239189527861e+02, -6.7744869054317850e-04, 4.5195192232412410e+01, 2.2998038589222207e-03, 2.9120943115132863e-01, 8.0073592652737891e-02, -8.4023335956971990e-01, -2.2931051383885306e+00, -2.9266650676425737e-01, -3.2109920594551683e-01, -7.5444920068123474e-03, 1.7334275515362012e+01, 1.9088885170084806e-03, 5.4155975118041177e+01, 1.7188222826493554e-04};
    for(int i=0; i < 16; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_h1_1(c), res, 1.0e-4) << i <<  " <- " << c << '\n';
    }
  }
};
