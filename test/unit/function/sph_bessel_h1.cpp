//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_h1_1 over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-1,1),
                              tts::randoms(-1,1))
              )
<typename T>(T a0, T a1)
{
  using u_t = eve::underlying_type_t<T>;
  auto i = kyosu::complex(u_t(0), u_t(1));
  auto h1_1 = [i](auto z){ return kyosu::sph_bessel_j1(z)+i*kyosu::sph_bessel_y1(z) ; };
  auto h2_1 = [i](auto z){ return kyosu::sph_bessel_j1(z)-i*kyosu::sph_bessel_y1(z) ; };
  auto z = kyosu::complex(a0, a1);
  auto re = kyosu::complex(a0);
  auto im = i*a1;
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h1_1(re), h1_1(re), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h1_1(im), h1_1(im), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h1_1(z) , h1_1(z) , tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h2_1(re), h2_1(re), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h2_1(im), h2_1(im), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h2_1(z) , h2_1(z) , tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::sph_bessel_h1_1 over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T , T )
{
  using kyosu::sph_bessel_h1_1;
  using kyosu::sph_bessel_h2_1;
  auto z =   kyosu::complex(T(0), T(0));
  TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_h1_1(z))));
  TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_h2_1(z))));
};
