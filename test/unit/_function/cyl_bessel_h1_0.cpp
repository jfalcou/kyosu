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
    std::array<T, 16> reres{5.4897235878702522e-05, -1.2268421138042991e+02, 6.2791919542924018e-04, -4.8089232666858855e+01, -2.4084160260729008e-03, 6.1781027538348077e-01, -6.6559203024245964e-02, 2.5605247393843049e+00, 9.7762624653829611e-01, 2.2744989480229472e-01, 9.8407508041674696e-01, 8.0887252704128568e-03, -1.8273514210562674e+01, -1.7457419869508024e-03, -6.1802005844609923e+01, -1.6987525206133878e-04};
    std::array<T, 16> imres{-6.5539561898233831e-05, 2.8056814033312583e+02, 3.7023665194116904e-04, -1.1742199634170285e+01, 6.1311336939828889e-03, -8.8084554422437513e+00, -1.6219886131682522e-02, -6.6297629083583021e-01, -8.0727357780451992e-01, -5.1055458673089568e-02, 3.6321658845974136e+00, 1.8052231450423499e-02, 7.4948386100868873e+00, 1.1896731293522277e-03, -1.0185845035564768e+02, -1.7463870535747248e-04};
    for(int i=0; i < 16; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_h1_0(c), res, 1.0e-4) << i <<  " <- " << c << '\n';
    }
  }
};