//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_yn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::cout.precision(17);
    std::array<T, 8> re{2.0309144503737393e+00, -1.5992515729134549e+00, 1.6982551054108397e+00, -1.3327549270623136e+00, 2.6585368919111341e-01, 7.3163244235853131e-01, -1.5491151507087859e+00, 2.4846599242220186e+00};

    std::array<T, 8> im{-1.4137922349350807e+00, -1.7357125614937789e+00, 4.0762417134967421e-02, -1.4645033242641059e+00, 1.5914290999536518e+00, 2.3057243858262124e+00, -2.2075167685839387e+00, -5.7866716195750623e-01};

    std::array<T, 8> reres{-4.4062036092080337e-01, -3.3967954461649441e-01, -1.5667619074526007e+00, -4.0477676250027339e-01, 5.9271179286244735e-01, 3.7250752149022126e-01, -4.0842410865380668e-01, -6.8424644495325704e-01};

    std::array<T, 8> imres{-3.6401836760736062e-01, -4.6948726732250373e-01, 8.0811726440696674e-02, -6.2890286218778024e-01, -8.1624047120865173e-01, -4.2529834100001956e-01,-5.2072912299547713e-01, -2.6673624676594038e-01};

    for(int i=0; i < 8; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_yn(3, c), res, 1.0e-6) << i <<  " <- " << c << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_yn over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T a0, T a1)
{
  using u_t = eve::underlying_type_t<T>;
  auto z =  kyosu::complex(a0, a1);
  auto re = kyosu::complex(eve::abs(a0));
  auto zer =   kyosu::complex(T(0), T(0));
  auto minf=   kyosu::complex(eve::minf(eve::as<T>()));
  {
    auto conjz =  kyosu::conj(z);

    for(int i=0; i <10 ; ++i)
    {
      auto ynz = kyosu::cyl_bessel_yn(i, z);
      TTS_IEEE_EQUAL(ynz, kyosu::conj(kyosu::cyl_bessel_yn(i, conjz)));
      auto yre = kyosu::cyl_bessel_yn(i, kyosu::abs(re));
      TTS_EXPECT(eve::all(kyosu::is_real(yre)))<< i << " -> " << yre << '\n';
      auto yzer =  kyosu::cyl_bessel_yn(i, zer);
      TTS_IEEE_EQUAL(yzer, minf);
      TTS_IEEE_EQUAL(ynz, eve::sign_alternate(u_t(i))*kyosu::cyl_bessel_yn(-i, z)) << i << '\n';
    }
  }
};
