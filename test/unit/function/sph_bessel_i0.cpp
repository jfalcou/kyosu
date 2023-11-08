//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_i1_0 over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10))
              )
<typename T>(T a0, T a1)
{
  auto i1_0 = [](auto z){ return kyosu::sinh(z)/z; };
  auto i2_0 = [](auto z){ return kyosu::cosh(z)/z; };
  using u_t = eve::underlying_type_t<T>;
  auto i = kyosu::complex(u_t(0), u_t(1));
  auto z = kyosu::complex(a0, a1);
  auto re = kyosu::complex(a0);
  auto im = i*a1;
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i1_0(re), i1_0(re), 1.0e-4) << i <<  " <- " << re << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i1_0(im), i1_0(im), 1.0e-4) << i <<  " <- " << im << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i1_0(z) , i1_0(z) , 1.0e-4) << i <<  " <- " << z << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i2_0(re), i2_0(re), 1.0e-4) << i <<  " <- " << re << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i2_0(im), i2_0(im), 1.0e-4) << i <<  " <- " << im << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i2_0(z) , i2_0(z) , 1.0e-4) << i <<  " <- " << z << '\n';
};

TTS_CASE_WITH ( "Check kyosu::sph_bessel_i1_0 over real"
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
  using kyosu::sph_bessel_i1_0;
  using kyosu::sph_bessel_i1_1;
  auto i1_0c = sph_bessel_i1_0(c);
  auto i1_1c = sph_bessel_i1_1(c);
  TTS_EQUAL(i1_0c, sph_bessel_i1_0(cm));
  TTS_EQUAL(i1_1c, -sph_bessel_i1_1(cm));
  TTS_EQUAL(i1_0c, kyosu::conj(sph_bessel_i1_0(cb)));
  TTS_EQUAL(i1_1c, kyosu::conj(sph_bessel_i1_1(cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(sph_bessel_i1_0(cr))));
  TTS_EXPECT(eve::all(kyosu::is_real(sph_bessel_i1_1(cr))));
  TTS_EXPECT(eve::all(kyosu::is_real(sph_bessel_i1_0(ci))));
  TTS_EXPECT(eve::all(kyosu::is_pure(sph_bessel_i1_1(ci))));
  auto z =   kyosu::complex(T(0), T(0));
  auto o =   kyosu::complex(T(1), T(0));
  TTS_EQUAL(sph_bessel_i1_0(z), o);
  TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_i1_1(z))));
};
