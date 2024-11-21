//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_h1_0 over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10))
              )
<typename T>(T a0, T a1)
{
  // auto prec = sizeof(eve::element_type_t<T>) == 8 ?  tts::prec<T>() : 1.e-3;
  using u_t = eve::underlying_type_t<T>;
  auto i = kyosu::complex(u_t(0), u_t(1));
  auto h1_0 = [i](auto z){ return kyosu::sph_bessel_j0(z)+i*kyosu::sph_bessel_y0(z) ; };
  auto h2_0 = [i](auto z){ return kyosu::sph_bessel_j0(z)-i*kyosu::sph_bessel_y0(z) ; };
  auto z = kyosu::complex(a0, a1);
  auto re = kyosu::complex(a0);
  auto im = i*a1;
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h1_0(re), h1_0(re), tts::prec<T>()) << i <<  " <- " << re << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h1_0(im), h1_0(im), tts::prec<T>()) << i <<  " <- " << im << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h1_0(z) , h1_0(z) , tts::prec<T>()) << i <<  " <- " << z << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h2_0(re), h2_0(re), tts::prec<T>()) << i <<  " <- " << re << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h2_0(im), h2_0(im), tts::prec<T>()) << i <<  " <- " << im << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h2_0(z) , h2_0(z) , tts::prec<T>()) << i <<  " <- " << z << '\n';
};

TTS_CASE_WITH ( "Check kyosu::sph_bessel_h1_0 over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T , T )
{
  using kyosu::sph_bessel_h1_0;
  using kyosu::sph_bessel_h1_1;
  auto z =   kyosu::complex(T(0), T(0));
  TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_h1_1(z))));
  TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_h1_0(z))));
};
