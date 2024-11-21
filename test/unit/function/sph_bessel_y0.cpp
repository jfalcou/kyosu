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
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10))
              )
<typename T>(T a0, T a1)
{
  using u_t = eve::underlying_type_t<T>;
  auto i = kyosu::complex(u_t(0), u_t(1));
  auto z = kyosu::complex(a0, a1);
  auto re = kyosu::complex(a0);
  auto im = i*a1;
  auto y0 = [](auto z){return -kyosu::cos(z)/z; };
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_y0(re), y0(re), 1.0e-4) << i <<  " <- " << re << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_y0(im), y0(im), 1.0e-4) << i <<  " <- " << im << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_y0(z) , y0(z) , 1.0e-4) << i <<  " <- " << z << '\n';
};

TTS_CASE_WITH ( "Check kyosu::sph_bessel_y0 over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T a0, T a1)
{
  // auto prec = 1.0e-6;
  auto c =  kyosu::complex(a0, a1);
  auto cb=  kyosu::conj(c);
  auto cm=  -c;
  auto cr=  kyosu::complex(a0);
  auto ci=  kyosu::complex(T(0), a1);
  using kyosu::sph_bessel_y0;
  auto y0c = sph_bessel_y0(c);
 //  TTS_EQUAL(y0c, -sph_bessel_y0(cm));
//   TTS_EQUAL(y0c, kyosu::conj(sph_bessel_y0(cb)));
  TTS_RELATIVE_EQUAL(y0c, -sph_bessel_y0(cm), tts::prec<T>());
  TTS_RELATIVE_EQUAL(y0c, kyosu::conj(sph_bessel_y0(cb)), tts::prec<T>());
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
  auto z =   kyosu::complex(T(0), T(0));
  TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_y0(z))));
};
