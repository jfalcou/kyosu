//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sph_bessel_h1nn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
//  using u_t = eve::underlying_type_t<T>;
  if constexpr(sizeof(T) == 8)
  {
    {
      std::array<T, 8> re{-3.0741715027083147e+00, 4.3426648638416063e+00, -2.7981941356021967e+00, -8.8600087717455200e-01, -2.1297833758572637e+00, -4.9849851779139147e+00, 1.5223768684011907e+00, -8.4260002884283591e-01};

      std::array<T, 8> im{-2.0307188187984737e+00, -4.0705193405198852e+00, 2.3547162061032791e+00, -2.5738011925258233e+00, 2.6849682520111706e+00, 2.5683492208093019e+00, 3.7050613060981217e+00, -1.9582614234846174e+00};

      std::array<T, 8> reres{-1.8987639369507804e+01, -9.7846582033372931e-02, 7.6790116788295499e+00, -2.0361029682674200e+02, -2.7927440764619799e+01, 1.3454938584765222e-01, 3.9201689873947365e+00, -1.6300834687965348e+03};

      std::array<T, 8> imres{2.1905468729751316e+00, -8.1937022872644705e-02, 1.6738406475084535e+01, 2.0527437676205267e+00, 3.5791027983986723e+00, -6.3121489926765517e-01, 3.4600793328396318e+00, -1.1728487363689339e+03};
      for(int i=0; i < 8; ++i)
      {
        auto c = kyosu::complex(re[i], im[i]);
        auto res = kyosu::complex(reres[i], imres[i]);
        TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h1n(8, c), res, 1.0e-4) << i <<  " <- " << c << '\n';
      }
    }
    {
      std::array<T, 8> re{4.8023241784273516e+00, -7.3624994664291843e-01, 2.7845895150886490e+00, -4.2439315522389700e+00, -3.2700626063635507e+00, 3.2777149501976064e+00, -1.7350443377902092e+00, 3.4240826382686604e+00};
      std::array<T, 8> im{-1.0943783015244868e+00, 4.2508564240326341e-01, -1.8583059717139760e+00, -4.8549618376057779e+00, 2.1934429650892029e+00, 2.7593426313960578e+00, -2.0573580642750766e+00, 8.2956711439982622e-01};
      std::array<T, 8> reres{ -2.537018910232239 ,-8841141.702494428,42.74928523513201,-0.006411322923734045,-10.58900986724366,-2.513588322804079,-252.9552712623419,32.93818432005056};
      std::array<T, 8> imres{-0.1086979192666555,+183900.2111111085,+10.09288763529341,-0.07774596762539486,-1.210214973107798,+3.719306160697736,-66.91213603662391,-12.65422016639942};
    for(int i=0; i < 8; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
       auto res = kyosu::complex(reres[i], imres[i]);
       TTS_RELATIVE_EQUAL(kyosu::sph_bessel_h2n(8, c), res, 1.0e-4);
      }
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
    auto cm = -c;
    auto zer =   kyosu::complex(T(0), T(0));
    using kyosu::sph_bessel_h1n;
    using kyosu::sph_bessel_h2n;

    for(int i=1; i < 4 ; ++i)
    {
      auto h1nc = sph_bessel_h1n(i, c);
      auto h2nc = sph_bessel_h2n(i, c);
      TTS_IEEE_EQUAL(h1nc, eve::sign_alternate(u_t(i))*sph_bessel_h2n(i, cm)) << "c " << c << "\n";
      TTS_IEEE_EQUAL(h2nc, eve::sign_alternate(u_t(i))*sph_bessel_h1n(i, cm)) << "c " << c << "\n";
      TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_h1n(i, zer)))) << i << sph_bessel_h1n(i, zer) << '\n';
      TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_h2n(i, zer)))) << i << sph_bessel_h2n(i, zer) << '\n';
    }
  }
};
