//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sph_bessel_yn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 8> re{2.9751292610110780e+00, 1.3139296459466121e+00, 3.2268716431231459e+00, 1.6502599567093656e+00, 4.6332810203103314e+00, 2.8212863760434983e+00, -1.1810230326333682e+00, 4.4699044019977441e+00};

    std::array<T, 8> im{-2.0222848019757578e+00, 4.6155627764756613e+00, 2.1866177359975039e+00, -1.5599498003423562e+00, 3.2640938797973753e+00, 1.4714931919159735e+00, -3.8260183135371872e+00, -2.1131147779384407e-01};

    std::array<T, 8> reres{-3.5158398033526106e-01, 4.9066840081936158e-01, -3.9771160672274486e-01, 3.4727405740898953e-01, -1.0049148303947214e-01, -2.9662326625355484e-01, 2.8364317746458689e-01, -1.1622279259142240e-01};

    std::array<T, 8> imres{-2.5850292463184665e-01, -2.8908255599320762e+00, 3.1145881726375613e-01, -2.6570747897125668e-01, 1.2559393288754663e+00, 3.0517784454448199e-01, -1.2282698054615229e+00, -4.3334436047326737e-02};
    for(int i=0; i < 8; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::sph_bessel_yn(3, c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::sph_bessel_yn over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T a0, T a1)
{
  if constexpr(sizeof(eve::underlying_type_t<T>) == 8)
  {
    using u_t = eve::underlying_type_t<T>;
    auto c =  kyosu::complex(a0, a1);
    auto cm=  -c;
    auto cr=  kyosu::complex(a0);
    auto ci=  kyosu::complex(T(0), a1);
    auto zer =   kyosu::complex(T(0), T(0));

    using kyosu::sph_bessel_yn;

    for(int i=2; i < 10 ; ++i)
    {
      auto ync = sph_bessel_yn(i, c);
      TTS_IEEE_EQUAL(ync, eve::sign_alternate(u_t(i+1))*sph_bessel_yn(i, cm)) << "i " << i << " c " << c << "\n";
      TTS_EXPECT(eve::all(kyosu::is_real(cr)));
      TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
      TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_yn(i, zer)))) << i << '\n';
    }
  }
};
