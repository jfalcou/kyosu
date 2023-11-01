//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_k0 over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  using e_t = eve::element_type_t<T>;
  if constexpr(sizeof(e_t) == 8)
  {
    std::cout.precision(17);
    std::array<T, 8> re{2.3584877349134130e+00, 9.0164385767932564e-01, -1.5393599740361523e+00, 1.5668095462351217e+00, 1.6179702389500128e+00, -5.5681137226619104e-01, -2.2990386896893691e+00, 1.9300383451287466e+00};

    std::array<T, 8> im{-8.0071372624748560e-01, 1.9823595245805736e+00, -1.3978761922193099e+00, -1.4654991890321578e+00, -5.3416883666219606e-01, -1.9265301646062505e+00, -1.6132600067568537e+00, -2.3575615216282779e+00};

    std::array<T, 8> reres{4.1782770293350736e-02, -2.7083150384809346e-01, -3.4769747409921696e+00, -4.0882933553504530e-02, 1.4002108258106824e-01, -1.4548439736185870e+00, -7.3832781780344741e+00, -9.4738063303879627e-02};

    std::array<T, 8> imres{5.8709121187673685e-02, -1.9749705340577356e-01, 2.3664976923056558e+00, 1.6665625358420463e-01, 1.1276125697599239e-01, 5.3154381678401141e-01, 2.2763972412185578e+00, 3.6519862966414102e-02};
    for(int i=0; i < 8; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_k0(c), res, 1.0e-4) << i <<  " <- " << c << '\n';
    }
  }
};

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_k0 over real"
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
  using kyosu::cyl_bessel_k0;
  auto k0c = cyl_bessel_k0(c);
  TTS_IEEE_EQUAL(k0c, kyosu::conj(cyl_bessel_k0(cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  auto z =   kyosu::complex(T(0), T(0));
  auto o =   kyosu::complex(T(1), T(0));
  TTS_IEEE_EQUAL(cyl_bessel_k0(z), o);
};
