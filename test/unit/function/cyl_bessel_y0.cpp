//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_y0 over real"
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
    std::array<T, 16> reres{3.7228503917670645e+02, 1.4028404905543897e+02, 2.7082105569100559e+01, -5.8700747454210846e+00, -8.2705253054270944e+00, -4.3994205881197939e+00, -1.5033646224991988e+00, -4.4146240608696213e-01, -8.0727357780451992e-01, 4.4547448893603253e-01, 1.8303018031687566e+00, 3.7536967330733093e+00, 3.7504872004100616e+00, -7.5438037834143987e+00, -5.0929260867841691e+01, -1.4801145866706489e+02};
    std::array<T, 16> imres{1.0994197036691477e+02, 6.1342228067111975e+01, -5.4746691895180255e+01, 2.4044970964177871e+01, -6.0660844500468452e+00, -3.1803969001486970e-01, 1.5191915481134708e+00, -1.3499548225851350e+00, 0.0000000000000000e+00, 7.1015858200373461e-01, -4.6313696776094526e-01, -1.8893883861394067e+00, 9.1358918130486799e+00, -2.2792749680635211e+01, 3.0900648285609595e+01, 2.3691500004012831e+01};

    for(int i=0; i < 16; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto ref = kyosu::complex(reres[i], imres[i]);
      auto res = kyosu::cyl_bessel_y0(c);
      TTS_RELATIVE_EQUAL(res, ref, 1.0e-4) << i <<  " <- " << c << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_y0 over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T a0, T a1)
{
 auto c =  kyosu::complex(a0, a1);
 auto cb=  kyosu::conj(c);
  auto cr=  kyosu::complex(a0);
  auto ci=  kyosu::complex(T(0), a1);
  using kyosu::cyl_bessel_y0;
  auto y0c = cyl_bessel_y0(c);
  TTS_IEEE_EQUAL(y0c, kyosu::conj(cyl_bessel_y0(cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
  auto z =   kyosu::complex(T(0), T(0));
  auto minf=   kyosu::complex(eve::minf(eve::as<T>()));
  TTS_IEEE_EQUAL(cyl_bessel_y0(z), minf);
};