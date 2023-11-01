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
    std::cout.precision(17);
    std::array<T, 8> re{1.3556565953650257e+00, 3.3014253671480853e+00, -2.5475601159592665e+00, 1.1681025625526764e+00, 2.0457564384951734e+00, -1.2532453407268573e+00, -4.7295944112409973e+00, -2.2840688135673504e+00};

    std::array<T, 8> im{4.0914290638525896e+00, -5.6356545999116547e-01, -3.6064274257830387e+00, 1.6951171853616265e+00, -1.3703722677989172e+00, -1.2563658033049907e+00, -6.3364633643107848e-01, 3.7665729797577785e+00};

    std::array<T, 8> reres{-7.6636006934291934e-01, 5.5235295932926602e+00, -2.4705435157985449e+00, 4.4277914531229978e-01, 1.0802715562231253e+00, 8.4386300461818664e-01, 1.8020770631855463e+01, -1.8995274844066037e+00};

    std::array<T, 8> imres{-2.1944572999838249e-01, -2.7986262396670361e+00, 8.7442069710394574e-02, 7.9022841347779427e-01, -1.7589863003105213e+00, 7.7297061965418656e-01, 1.1358027174716181e+01, 1.6926234813445529e-01};


    for(size_t i=0; i < re.size(); ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i0(c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }
  std::cout.precision(17);

  std::array<T, 8> re{1.1554018562666468e-01, 5.3044189227319072e-01, 3.5245310048347744e-01, 3.2527350287655354e-01, 2.4688936247411308e+00, -5.1146428618899231e-01, 1.6635701653597774e+00, -1.7452778188732947e+00};

  std::array<T, 8> im{-1.7178778650082149e+00, -6.2417426685100863e-01, -1.3610935539710856e+00, 8.2783355400980418e-01, -2.3894194571359355e+00, 2.0229766336828989e+00, 1.3374638218449837e+00, 1.3919200132871019e+00};

  std::array<T, 8> reres{3.8798556902950510e-01, 9.6633789815319027e-01, 5.9999039779438423e-01, 8.5597095083560792e-01, -1.0143179716268755e+00, 2.0074991801689268e-01, 9.2740840079896603e-01, 8.9681286936021443e-01};

  std::array<T, 8> imres{-6.6973566887490954e-02, -1.6318950520829845e-01, -1.9129702196723380e-01, 1.2505065943633600e-01, -2.3797492378710814e+00, -3.0313550122100480e-01, 1.2137193362618577e+00, -1.3377794267565666e+00};

  for(int i=0; i < 8; ++i)
  {
    auto c = kyosu::complex(re[i], im[i]);
    auto res = kyosu::complex(reres[i], imres[i]);
    double tol = (sizeof(e_t) == 4) ? 4.e-3 :1.e-7;
    TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i0(c), res, tol) << i <<  " <- " << c << '\n';
    TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i0(3+re[i]), kyosu::real(kyosu::cyl_bessel_i0(kyosu::complex(3+re[i], e_t(0.0)))), tol)<< re[i] << '\n';
    TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i0(3+im[i]), kyosu::real(kyosu::cyl_bessel_i0(kyosu::complex(3+im[i], e_t(0.0)))), tol)<< re[i] << '\n';
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
