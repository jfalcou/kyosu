//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_in over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};
    std::array<T, 16> reres2{-7.1969079270007995e+01, -1.5683393966879203e+01, 1.0466294168141445e+01, 1.0748175707345291e+01, 3.8758917427989048e+00, -4.0451627051867489e-01, -1.3871137761167767e+00, -1.9986198478844575e+00, 2.1745740283593154e+01, -3.5495344133093099e-01, -2.1599306055793810e-01, -6.4128726120274343e-02, 5.9177725553375728e-05, 1.1059920812797431e-02, 5.5392221151187348e-03, 6.0101021352945098e-04};
    std::array<T, 16> imres2{-1.2683509501122607e+01, 3.4965859052136359e+01, -1.7316514091627536e+01, 8.3661819724535313e-01, 4.3427874804402400e+00, -3.1957333499958636e+00, 1.3566078701770719e+00, -1.3325273444493084e+00, 0.0000000000000000e+00, -8.4156523861025967e-01, 6.3585420268451043e-02, 4.6616485973025479e-02, -3.1692375622982084e-02, 7.6873285860862006e-03, 2.1150331597556389e-03, -2.6011826078990870e-03};

    for(size_t i=0; i < re.size(); ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      int j = 0;
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_kn(j, c), kyosu::cyl_bessel_k0(c), tts::prec<T>()) << i <<  " <- " << c << '\n';
      j = 1;
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_kn(j, c), kyosu::cyl_bessel_k1(c), tts::prec<T>()) << i <<  " <- " << c << '\n';
      j = 2;
      auto res = kyosu::complex(reres2[i], imres2[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_kn(j, c), res, tts::prec<T>()) << i <<  " <- " << c << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_kn over real"
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
  auto zer =   kyosu::complex(T(0), T(0));
  auto inf =   kyosu::complex(eve::inf(eve::as<T>()));

  using kyosu::cyl_bessel_kn;

 for(int i=0; i < 10; ++i)
 {
  auto knc = cyl_bessel_kn(i, c);
  TTS_IEEE_EQUAL(knc, kyosu::conj(cyl_bessel_kn(i, cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
  TTS_IEEE_EQUAL(cyl_bessel_kn(i, zer), inf) << i << '\n';
  TTS_IEEE_EQUAL(knc, cyl_bessel_kn(-i, c));
 }
};
