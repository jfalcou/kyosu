//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_j0 over real"
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
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_j0(re), kyosu::sinc(re), tts::prec<T>()) << i <<  " <- " << re << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_j0(im), kyosu::sinc(im), tts::prec<T>()) << i <<  " <- " << im << '\n';
  TTS_RELATIVE_EQUAL(kyosu::sph_bessel_j0(z) , kyosu::sinc(z) , tts::prec<T>()) << i <<  " <- " << z << '\n';
};

TTS_CASE_WITH ( "Check kyosu::sph_bessel_j0 over real"
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
  using kyosu::sph_bessel_j0;
  auto j0c = sph_bessel_j0(c);
//   TTS_EQUAL(j0c, sph_bessel_j0(cm));
//   TTS_EQUAL(j0c, kyosu::conj(sph_bessel_j0(cb)));
  TTS_RELATIVE_EQUAL(j0c, sph_bessel_j0(cm), tts::prec<T>());
  TTS_RELATIVE_EQUAL(j0c, kyosu::conj(sph_bessel_j0(cb)), tts::prec<T>());
  std::cout << "dist" <<  std::hexfloat << kyosu::abs(j0c - kyosu::conj(sph_bessel_j0(cb))) << std::endl;
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
  auto z =   kyosu::complex(T(0), T(0));
  auto o =   kyosu::complex(T(1), T(0));
  TTS_IEEE_EQUAL(sph_bessel_j0(z), o);
};
