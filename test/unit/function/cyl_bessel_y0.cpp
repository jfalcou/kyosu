//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::abs over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  using e_t = eve::element_type_t<T>;
  if constexpr(sizeof(e_t) == 8)
  {
    std::cout.precision(17);
std::array<T, 8> re{1.5381976949805014e+00, 2.6255594034478125e+00, 4.0600216654926253e+00, 3.0266655455424605e+00, 1.3448905656094086e+00, 2.4249586939460772e+00, 3.1124857827487764e+00, 1.4345560293678910e+00};

std::array<T, 8> im{2.5607710877709762e+00, 2.8452223336801215e+00, 1.9934297821004714e+00, 1.4123776635064056e+00, 1.9313288418481178e+00, 7.3411510697362348e-01, 1.7244519681227217e+00, 1.9474201604198005e+00};

std::array<T, 8> reres{2.9342027269323112e+00, 2.8408742765790516e+00, -4.5337528338235050e-01, 6.4439946072135390e-01, 1.5723708168034416e+00, 6.3470970747597821e-01, 7.0728489095068403e-01, 1.6495724050201730e+00};

std::array<T, 8> imres{9.9878589941422025e-01, -2.1771605668374145e+00, -1.2883253536336257e+00, -6.6033776889957740e-01, 9.8087741660078565e-01, -1.0108349995732357e-01, -9.7791998011643821e-01, 8.5834405245176992e-01};

    for(size_t i=0; i < re.size(); ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_y0(c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }
  std::cout.precision(17);


//   for(int i=0; i < 8; ++i)
//   {
//     auto c = kyosu::complex(re[i], im[i]);
//     auto res = kyosu::complex(reres[i], imres[i]);
//     double tol = (sizeof(e_t) == 4) ? 4.e-3 :1.e-7;
//     TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_y0(c), res, tol) << i <<  " <- " << c << '\n';
//      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_y0(3+re[i]), kyosu::real(kyosu::cyl_bessel_y0(kyosu::complex(3+re[i], e_t(0.0)))), tol)<< re[i] << '\n';
//      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_y0(3+im[i]), kyosu::real(kyosu::cyl_bessel_y0(kyosu::complex(3+im[i], e_t(0.0)))), tol)<< re[i] << '\n';
//   }
};
