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
    std::array<T, 8> re{-4.1836770228521267e+01, -4.1682207527601065e+01, -4.0619579092445747e+01, -4.4234864207453732e+01, -4.3110416350751848e+01, -4.3626638817587562e+01, -4.4580540281737981e+01, -4.1708122005195847e+01};

    std::array<T, 8> im{-4.4724569983549614e+01, -4.6490400566267638e+01, -4.7317594550520738e+01, -4.1337120165516517e+01, -4.1276020002765804e+01, -4.6670524375443286e+01, -4.9467141247871425e+01, -4.1317766188944873e+01};

    std::array<T, 8> reres{-7.0768747466033056e+16, 3.1730270005558764e+16, 2.1418055599841040e+16, 8.2313395058512320e+17, 2.7095441733811123e+17, 2.8742948492120032e+17, -3.9196223386893542e+17, 6.7047683494482400e+16};

    std::array<T, 8> imres{-2.4828379933328692e+16, -5.5176086947198392e+16, -5.0690181071974150e+15, 1.0336610466678229e+17, 1.5700946940956764e+16, -3.3290723855674362e+17, 1.0476061068394980e+18, 6.1360655674202130e+15};

    for(size_t i=0; i < re.size(); ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i1(c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }
  std::cout.precision(17);
  std::array<T, 8> re{-2.0045932610658785e+00, 1.5610767253921298e-02, 1.2016964006673581e+00, -1.4746256231752448e+00, 3.8509464414269778e-01, 4.3119169358173060e-01, 1.8117761375602393e-01, 2.2535543048838065e+00};

  std::array<T, 8> im{-1.3262936608790188e+00, 7.3358653580584687e-01, -7.7829729505626277e-01, 1.8039445371160530e+00, -3.9048140529175879e-01, 2.3733805921203750e+00, 4.1558677759532259e-01, -2.2418145868867645e-01};

  std::array<T, 8> reres{-6.2705259908555033e-01, 6.2883477739884225e-03, 5.5729657365627117e-01, -7.6451650900684065e-03, 1.8501953906506874e-01, -9.1123456107294123e-02, 8.5137403913618320e-02, 1.9707184262439041e+00};

  std::array<T, 8> imres{-1.5400427522131701e+00, 3.4269774692177124e-01, -5.7403352720521417e-01, 1.0985982884231822e+00, -2.0228216987024109e-01, 5.5832300258201450e-01, 2.0584212281549297e-01, -4.1012541772916467e-01};

  for(int i=0; i < 8; ++i)
  {
    auto c = kyosu::complex(re[i], im[i]);
    auto res = kyosu::complex(reres[i], imres[i]);
    double tol = (sizeof(e_t) == 4) ? 4.e-3 :1.e-7;
    TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i1(c), res, tol) << i <<  " <- " << c << '\n';
    TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i1(3+re[i]), kyosu::real(kyosu::cyl_bessel_i1(kyosu::complex(3+re[i], e_t(0.0)))), tol)<< re[i] << '\n';
    TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_i1(3+im[i]), kyosu::real(kyosu::cyl_bessel_i1(kyosu::complex(3+im[i], e_t(0.0)))), tol)<< re[i] << '\n';
  }
};

TTS_CASE_WITH ( "Check kyosu::abs over real"
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
  using kyosu::cyl_bessel_i1;
  auto i1c = cyl_bessel_i1(c);
  TTS_IEEE_EQUAL(i1c, -cyl_bessel_i1(cm));
  TTS_IEEE_EQUAL(i1c, kyosu::conj(cyl_bessel_i1(cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
};
