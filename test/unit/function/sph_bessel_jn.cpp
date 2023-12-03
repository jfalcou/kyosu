//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sph_bessel_jn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 8> re{-3.5864413497599945e-01, 1.8305506745510136e+00, 4.8145177703097399e+00, 4.7301901125586436e+00, -4.3947566261794710e+00, 1.0212518380533187e+00, -4.1514744061148807e+00, 1.2766581423615309e-01};

    std::array<T, 8> im{-1.4900727734412866e+00, 4.3733972760463349e+00, 6.3220189518343628e-01, 5.1967694618977767e-01, 6.2761895523580580e-01, 3.8772322566505766e+00, -4.6074082935612806e+00, -4.4849065338089478e+00};

    std::array<T, 8> reres{2.6695000315635153e-02, -2.2215759788276843e+00, 2.5805202705605512e-01, 2.5337598654371535e-01, -2.6051834312740757e-01, -1.1816979617769454e+00, -3.2042363997219185e+00, -3.3242357291991742e-01};

    std::array<T, 8> imres{2.7709520397028151e-02, 9.1259760936216550e-01, -1.9344122386863866e-02, -1.1252144284238647e-02, 8.5011995341820815e-03, -5.1276579958119139e-01, -2.1027562948226137e+00, 2.3711156404785037e+00};
    for(int i=0; i < 8; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::sph_bessel_jn(3, c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::sph_bessel_jn over real"
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
    auto cb=  kyosu::conj(c);
    auto cm=  -c;
    auto cr=  kyosu::complex(a0);
    auto ci=  kyosu::complex(T(0), a1);
    auto zer =   kyosu::complex(T(0), T(0));
    auto one =   kyosu::complex(T(1), T(0));

    using kyosu::sph_bessel_jn;

    for(int i=0; i < 10 ; ++i)
    {
      auto jnc = sph_bessel_jn(i, c);
      TTS_IEEE_EQUAL(jnc, eve::sign_alternate(u_t(i))*sph_bessel_jn(i, cm)) << "c " << c << "\n";
      TTS_IEEE_EQUAL(jnc, kyosu::conj(sph_bessel_jn(i, cb)));
      TTS_EXPECT(eve::all(kyosu::is_real(cr)));
      TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
      TTS_IEEE_EQUAL(sph_bessel_jn(i, zer), i ? zer : one) << i << '\n';
    }
  }
};
