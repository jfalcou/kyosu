//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_y1 over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  using e_t = eve::element_type_t<T>;
  if constexpr(sizeof(e_t) == 8)
  {
    std::array<T, 8> re{6.5758573026995004e-01, -2.4649387808542378e+00, 1.9205766369481703e+00, -6.9739731404600436e-01, 4.4532863650021348e-01, 2.4757649834958393e+00, -5.3435309039155832e-01, -2.4349028761454212e+00};

    std::array<T, 8> im{1.2035170114779326e+00, -3.5932055457567835e-01, 8.3662582734559288e-01, 2.2469103234867700e+00, -9.1023149008937376e-01, 2.4818838321237546e-01, 1.5847819595769823e+00, -1.3967310652706204e+00};

    std::array<T, 8> reres{-8.1045682169396482e-01, 2.3820060953407891e-02, -9.3267933254955498e-02, -1.5790753753124993e+00, -7.5013324227681488e-01, 1.4423021239534972e-01, -8.5123355830924607e-01, 4.3341743806150423e-01};

    std::array<T, 8> imres{6.3354487728865994e-01, 8.9036262959787016e-01, 5.0186176942328398e-01, -1.1543670775735402e+00, -5.8526040753707131e-01, 1.1142422613715078e-01, -4.3418909281427642e-01, 1.0069485325105600e+00};

    for(int i=0; i < 8; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_y1(c), res, 1.0e-4) << i <<  " <- " << c << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_y1 over real"
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
  using kyosu::cyl_bessel_y1;
  auto y1c = cyl_bessel_y1(c);
  TTS_IEEE_EQUAL(y1c, kyosu::conj(cyl_bessel_y1(cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
  auto z =   kyosu::complex(T(0), T(0));
  auto minf=   kyosu::complex(eve::minf(eve::as<T>()));
  TTS_IEEE_EQUAL(cyl_bessel_y1(z), minf);
};
