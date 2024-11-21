//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_k1 over real"
              , kyosu::scalar_real_types
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
  auto k0 = [](auto z){ return  eve::pio_2(eve::as<u_t>())*kyosu::exp(-z)/z; };
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_k0(re), k0(re), tts::prec<T>()) << i <<  " <- " << re << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_k0(im), k0(im), tts::prec<T>()) << i <<  " <- " << im << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_k0(z) , k0(z) , tts::prec<T>()) << i <<  " <- " << z << '\n';
};

TTS_CASE_WITH ( "Check kyosu::sph_bessel_k0 over real"
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
  auto ci=  kyosu::complex(T(0), a1);
  using kyosu::sph_bessel_k0;
  auto k0c = sph_bessel_k0(c);
  TTS_EQUAL(k0c, kyosu::conj(sph_bessel_k0(cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
  auto z =   kyosu::complex(T(0), T(0));
  TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_k0(z))));
};
