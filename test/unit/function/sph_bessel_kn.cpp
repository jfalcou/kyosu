//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sph_bessel_kn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 8> re{2.0344637669563861e+00, -4.3813469489459145e+00, -2.6657638099374692e+00, 3.3889708858072520e+00, -3.7647998208558220e+00, 1.7491848302215496e+00, 6.6959832811814834e-02, -1.0359975448622161e+00};

    std::array<T, 8> im{9.1599183409523333e-01, 3.8563462289706973e-01, 3.1031208865787474e-01, -3.1600822008299359e+00, 4.0144397073512161e+00, -3.6311009559927134e+00, -2.8259820882536459e+00, 4.1712992187897164e+00};

    std::array<T, 8> reres{-1.4678177240255734e+03, -1.7772703403589662e+00, -1.6005659389435411e+02, 1.1469395680075878e+00, 2.9114121290916373e-01, -6.8942371077974842e+00, 7.2045172227253374e+01, -1.0631979003342050e+01};

    std::array<T, 8> imres{1.4756336825094897e+03, -2.1777133097986439e+00, -3.1159733154561093e+02, 2.7355335304581043e+00, -5.3062640683955642e-01, -1.4181875854319991e+01, 3.5537641050392568e+02, 3.3112069122251264e+00};
     for(int i=0; i < 8; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::sph_bessel_kn(8, c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::sph_bessel_kn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T a0, T a1)
{
  if constexpr(sizeof(eve::underlying_type_t<T>) == 8)
  {
    auto cr=  kyosu::complex(a0);
    auto ci=  kyosu::complex(T(0), a1);
    auto zer =   kyosu::complex(T(0), T(0));

    using kyosu::sph_bessel_kn;

    for(int i=2; i < 10 ; ++i)
    {
      TTS_EXPECT(eve::all(kyosu::is_real(cr)));
      TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
      TTS_EXPECT(eve::all(kyosu::is_nan(sph_bessel_kn(i, zer)))) << i << '\n';
    }
  }
};
