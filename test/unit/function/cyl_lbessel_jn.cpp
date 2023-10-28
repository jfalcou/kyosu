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
  if constexpr(sizeof(T) == 8)
  {
    std::cout.precision(17);
    std::array<T, 10> re{ -9.8403264736233908e+01, 8.6287324687322851e+01, 2.8677183208357349e+01, 7.5642931882481321e+01, 9.6351793077594323e+01
        , -7.8716695947540288e+01, -5.0019457963533974e+01, 5.9030075032843811e+01, -7.5596124248257235e+00, 8.5810875418338028e+01};
    std::array<T, 10> im{-1.9271037994246587e+01, 7.9043790847200569e+01, -3.0599555605285602e+01, -7.1720588923445590e+01, -6.1110206702938363e+01
        , 9.0167523214068439e+01, -7.0131934820406244e+01, -9.3405497312943496e+01, 8.3431692318213322e+01, -4.1557438097347173e+01};

    std::array<T, 10> reres{-3.3279158735087640e+06, 6.7446373092398792e+32, 1.0973422267168294e+11, 6.9510412682541761e+28, -1.2657523599731811e+25,
        8.0429582124849094e+36, -5.9430267579521807e+28, -1.0741846420111567e+39, 6.6950456879149885e+34, 2.0245919743884628e+16};
    std::array<T, 10> imres{-8.6289796115820184e+06, 3.6264735895350172e+32, -1.1056118662675706e+12, 5.2905159458975805e+29, -7.9797425680943093e+23,
        5.0551834834322169e+37, 1.0236118318065309e+29, -8.1681100953492296e+38, -2.3290495380992445e+34, -3.9909835121233848e+16};
    for(int i=0; i < 10; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_jn(3, c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }

  std::array<T, 8> re{-2.2013892240657134e+00, -2.8382367527759522e-01, -7.0737598522551182e-01, 8.6178612999047166e-02, 1.8217799341954277e-01, -7.6718326053284047e-01, -5.9167207480492257e-01, 7.5911892713725948e-01};

  std::array<T, 8> im{8.7228967955690240e-01, -2.1140894389723703e+00, 2.2905192466959483e+00, -1.5275122978034243e+00, 5.5435596674685006e-01, -1.1418929858153533e+00, 1.1666506779144503e+00, -1.9198575359478032e+00};

  std::array<T, 8> reres{-1.3672173596226031e-01, 1.2004993008474076e-01, 3.4070032613198098e-01, -1.5845109266378627e-02, -3.4617874091075179e-03, 5.4024365099246512e-02, 4.9541047773116346e-02, -2.1467277569289250e-01};

  std::array<T, 8> imres{1.6497274394928027e-01, 2.3540711137379494e-01, -1.7769121638069371e-01, 8.4636178354763933e-02, -2.3973187185149024e-03, -1.7452629167850800e-02, -3.8485807736362864e-03, 5.8435910432745555e-02};
  using e_t = eve::element_type_t<T>;

  for(size_t i=0; i < re.size(); ++i)
  {
    auto c = kyosu::complex(re[i], im[i]);
    auto res = kyosu::log(kyosu::complex(reres[i], imres[i]));
    double tol = (sizeof(e_t) == 4) ? 1.e-3 :1.e-7;
    TTS_RELATIVE_EQUAL(kyosu::cyl_lbessel_jn(3, c), res, tol) << i <<  " <- " << c << '\n';
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
  if constexpr(sizeof(T) == 8)
  {
    using e_t = eve::element_type_t<T>;
    double tol = (sizeof(e_t) == 4) ? 1.e-3 :1.e-7;
    auto c =  kyosu::complex(a0, a1);
    auto cb=  kyosu::conj(c);
    auto cm=  -c;
    auto cr =  kyosu::complex(eve::abs(a0));
    using kyosu::cyl_lbessel_jn;
    using kyosu::cyl_bessel_jn;
    auto ljnc = cyl_lbessel_jn(3, c);
    auto logjnc = kyosu::log(cyl_bessel_jn(3, c));
    TTS_RELATIVE_EQUAL(ljnc, logjnc, tol) << "c " << c << "\n";

    auto ljncb = cyl_lbessel_jn(3, cb);
    auto logjncb = kyosu::log(cyl_bessel_jn(3, cb));
    TTS_RELATIVE_EQUAL(ljncb, logjncb, tol) << "c " << c << "\n";

    auto ljncm = cyl_lbessel_jn(3, cm);
    auto logjncm = kyosu::log(cyl_bessel_jn(3, cm));
    TTS_RELATIVE_EQUAL(ljncm, logjncm, tol) << "c " << c << "\n";
    TTS_EXPECT(eve::all(kyosu::is_real(kyosu::cyl_lbessel_jn(3, cr))));
//   TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
    auto z =   kyosu::complex(T(0), T(0));
    TTS_IEEE_EQUAL(cyl_lbessel_jn(3, z), kyosu::complex(eve::minf(eve::as<e_t>())));
  }
};
