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
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  using e_t = eve::element_type_t<T>;
  if constexpr(sizeof(e_t) == 8)
  {
    std::cout.precision(17);
    std::array<T, 8> re{-7.3954299670486945e-01, -3.7928780215327196e-02, -1.4509312401953633e+00, 2.2964197111982774e+00, -7.9699549838500194e-01, 5.4099472045802843e-01, -5.8957905551605738e-01, -5.1146527014834298e-01};

    std::array<T, 8> im{-2.1345822747239773e+00, -3.3484907524396035e-01, 2.2665940322875286e+00, -1.0045032564810230e+00, -2.4392625060316648e+00, 2.6547418070570761e-01, -2.3352892270792931e+00, 1.3879256025736524e+00};

    std::array<T, 8> reres{-1.7027762686598518e+00, -5.8170412824877404e-01, -2.9141064941382457e+00, 2.7872334701787467e-02, -1.5779496640047279e+00, 1.1145462290717538e+00, -1.3982594001564612e+00, -1.4628928686130445e+00};

    std::array<T, 8> imres{-1.9261773906655510e-01, 3.2589115393837513e+00, 1.0075935641554303e+00, 8.5373399021791460e-02, -6.4553389686343909e-01, -7.8086954815494913e-01, -3.6962699681190719e-01, -8.7620662002477645e-01};
    for(int i=0; i < 8; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_k1(c), res, 1.1e-6) << i <<  " <- " << c << " -- "<< kyosu::arg(c) << '\n';
    }
  }
};

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_k1 over real"
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
  using kyosu::cyl_bessel_k1;
  auto k1c = cyl_bessel_k1(c);
  TTS_IEEE_EQUAL(k1c, kyosu::conj(cyl_bessel_k1(cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  auto z =   kyosu::complex(T(0), T(0));
  auto o =   kyosu::complex(T(1), T(0));
  TTS_IEEE_EQUAL(cyl_bessel_k1(z), o);

};
