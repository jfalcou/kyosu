//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_i1 over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10))
              )
<typename T>(T a0, T a1)
{
  auto i1_1 = [](auto z){
    auto [sh, ch] = kyosu::sinhcosh(z);
    auto rz =  kyosu::rec(z);
    return  kyosu::fnma(sh, rz, ch)*rz;
  };
  auto i2_1 = [](auto z){
    auto [sh, ch] = kyosu::sinhcosh(z);
    auto rz =  kyosu::rec(z);
    return  kyosu::fnma(ch, rz, sh)*rz;
  };
  using u_t = eve::underlying_type_t<T>;
  auto i = kyosu::complex(u_t(0), u_t(1));
  auto z = kyosu::complex(a0, a1);
  auto re = kyosu::complex(a0);
  auto im = i*a1;
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i1_1(re), i1_1(re), tts::prec<T>()); //<< i <<  " <- " << re << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i1_1(im), i1_1(im), tts::prec<T>()); //<< i <<  " <- " << im << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i1_1(z) , i1_1(z) , tts::prec<T>()); //<< i <<  " <- " << z << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i2_1(re), i2_1(re), tts::prec<T>()); //<< i <<  " <- " << re << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i2_1(im), i2_1(im), tts::prec<T>()); // << i <<  " <- " << im << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i2_1(z) , i2_1(z) , tts::prec<T>()); //<< i <<  " <- " << z << '\n';
};

TTS_CASE_WITH ( "Check kyosu::sph_bessel_i1 over real"
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
  using kyosu::sph_bessel_i1_1;
  using kyosu::sph_bessel_i2_1;
  auto i1c = sph_bessel_i1_1(c);
  auto i2c = sph_bessel_i2_1(c);

  TTS_RELATIVE_EQUAL(i1c, -sph_bessel_i1_1(cm), tts::prec<T>());
  TTS_RELATIVE_EQUAL(i2c, sph_bessel_i2_1(cm), tts::prec<T>());
  TTS_RELATIVE_EQUAL(i1c, kyosu::conj(sph_bessel_i1_1(cb)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(i2c, kyosu::conj(sph_bessel_i2_1(cb)), tts::prec<T>());
  TTS_EXPECT(eve::all(kyosu::is_real(sph_bessel_i1_1(cr))));
  TTS_EXPECT(eve::all(kyosu::is_real(sph_bessel_i2_1(cr))));
  TTS_EXPECT(eve::all(kyosu::is_pure(sph_bessel_i1_1(ci))));
  TTS_EXPECT(eve::all(kyosu::is_real(sph_bessel_i2_1(ci))));
  auto z =   kyosu::complex(T(0), T(0));
  TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_i1_1(z))));
  TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_i2_1(z))));

};
