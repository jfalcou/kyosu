//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sph_bessel_i1nn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    {
      std::array<T, 8> re{-1.3102964777073500e+00, 2.6429797151271517e+00, -1.2991425964097203e+00, -2.0616201216776595e+00, -3.5692327918927735e-01, 4.5409169416450617e+00, 1.3915394762511490e+00, -1.5742664543118334e+00};
      std::array<T, 8> im{-4.9978344205200456e+00, 4.6966388867930240e+00, 4.5575687436111947e+00, -4.3856054937978231e+00, 1.7496198325295331e+00, -4.8976206253867760e+00, -2.2292456733273172e+00, -3.6547854593577123e+00};
      std::array<T, 8> reres{-8.9448633564799367e-04, -1.3550451109077518e-02, -1.4079674805043841e-03, -5.9344800455695375e-03, -1.6670926554323534e-08, 1.0879026036746578e-02, -2.4460612590389117e-05, -1.3445907340862448e-03};
      std::array<T, 8> imres{-7.8433567383746679e-03, 3.9123036962636004e-03, 4.2071250786199152e-03, -7.1820574884934665e-04, 2.7760904475739103e-06, -1.1171678180080313e-01, -5.5883425389321553e-05, -2.7135427306845860e-04};
      for(int i=0; i < 8; ++i)
      {
        auto c = kyosu::complex(re[i], im[i]);
        auto res = kyosu::complex(reres[i], imres[i]);
        TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i1n(8, c), res, 1.0e-7) << i <<  " <- " << c << '\n';
      }
    }
    {
      std::array<T, 8> re{-1.0353298912411590e+00, -4.0590492982139348e-01, -3.7533860841866939e+00, 2.5026965372926147e-01, 1.3027543743434511e-01,-3.9640689770100854e+00, -1.0995476278801330e+00, -3.8763377787749520e-01};
      std::array<T, 8> im{-4.2831047668722677e+00, 7.7061553129385785e-01, 1.3657001488056097e+00, 4.1210952543771051e-01, 4.4818969533279871e+00, -3.7525013370467541e+00, 4.8289663184328813e-01, -7.0094140409912353e-01};
      std::array<T, 8> reres{-5.7006149471406644e+00, 6.6457154244604167e+06, 4.9722413633652538e+00, -1.4179514732481084e+09, 1.2132650006681511e+00, -4.7090187937440880e-02, 3.0782381172903924e+05, 1.4851214398026228e+07};
      std::array<T, 8> imres{-1.3655417114292883e+00, 2.5782447371366373e+06, 1.6560730551132823e+00, -2.7650888434981310e+08, -5.5042068213386841e+00, 4.0322394841215375e-01, 2.1882447301295877e+05, -2.7656213800463108e+06};
      for(int i=0; i < 8; ++i)
      {
        auto c = kyosu::complex(re[i], im[i]);
        auto res = kyosu::complex(reres[i], imres[i]);
        TTS_RELATIVE_EQUAL(kyosu::sph_bessel_i2n(8, c), res, 1.0e-7) << i <<  " <- " << c << '\n';
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
    //   auto one =   kyosu::complex(T(1), T(0));

    using kyosu::sph_bessel_i1n;
    using kyosu::sph_bessel_i2n;

    for(int i=1; i < 4 ; ++i)
    {
      auto i1nc = sph_bessel_i1n(i, c);
      auto i2nc = sph_bessel_i2n(i, c);
      TTS_IEEE_EQUAL(i1nc, eve::sign_alternate(u_t(i))*sph_bessel_i1n(i, cm)) << "c " << c << "\n";
      TTS_IEEE_EQUAL(i2nc, eve::sign_alternate(u_t(i+1))*sph_bessel_i2n(i, cm)) << "c " << c << "\n";
      TTS_EXPECT(eve::all(kyosu::is_eqz(sph_bessel_i1n(i, zer)))) << i << sph_bessel_i1n(i, zer) << '\n';
      TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_i2n(i, zer)))) << i << sph_bessel_i2n(i, zer) << '\n';
    }
  }
};
