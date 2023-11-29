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
    std::array<T, 8> re{2.4955917718518910e+00, -1.6982259765731111e+00, 1.2315182267355251e+00, 2.1258824905764118e+00, -2.1711533910447676e+00, 9.1742698952666013e-01, -2.5479731910545422e-02, 1.4924891723416751e+00};

    std::array<T, 8> im{-5.0148281002365624e-01, 2.0253551112861641e+00, -5.0175898965530097e-01, -4.0455814438323523e-01, -2.1923016231568171e-01, -1.3185119199506317e+00, 1.0779142409536568e+00, 1.2528910061509635e-01};

    std::array<T, 8> reres{5.5469839057084858e-01, -1.8165994943959307e+00, 3.3680718591187470e-01, 5.6362426783532593e-01, 2.8645154466364819e-01, 6.0960351781866107e-01, -2.5569311956619334e-01, 3.8450178879111341e-01};

    std::array<T, 8> imres{7.8480890054575703e-02, 5.8352584787301165e-01, -2.9298142302554275e-01, -1.2803370889276175e-02, -2.4399346361135993e-01, -9.9087866505382638e-01, 1.3205924969979352e+00, 5.2208242352489359e-02};


    for(int i=4; i < 5; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_yn(0, c), res, 1.0e-4) << i <<  " <- " << c << '\n';
    }
  }
};


// TTS_CASE_WITH ( "Check kyosu::cyl_bessel_y0 over real"
//               , kyosu::real_types
//               , tts::generate(tts::randoms(-10,10),
//                               tts::randoms(-10,10)
//                              )
//               )
// <typename T>(T a0, T a1)
// {
//   auto c =  kyosu::complex(a0, a1);
//   auto cb=  kyosu::conj(c);
//   auto cr=  kyosu::complex(a0);
//   auto ci=  kyosu::complex(T(0), a1);
//   using kyosu::cyl_bessel_y0;
//   auto y0c = cyl_bessel_y0(c);
//   TTS_IEEE_EQUAL(y0c, kyosu::conj(cyl_bessel_y0(cb)));
//   TTS_EXPECT(eve::all(kyosu::is_real(cr)));
//   TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
//   auto z =   kyosu::complex(T(0), T(0));
//   auto minf=   kyosu::complex(eve::minf(eve::as<T>()));
//   TTS_IEEE_EQUAL(cyl_bessel_y0(z), minf);
// };
