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
    std::cout.precision(17);
    std::array<T, 8> re{1.4376454063874640e+00, -1.0673204704071071e-01, -1.0828666774506268e+00, -7.9765980000519210e-01, 4.2409189866361996e-01,7.6608496996954323e-01, -2.2849830522845975e+00, 4.3813679108628711e-01};

    std::array<T, 8> im{-2.5175040147125849e-01, 6.2364116715495577e-01, 1.1653810042557073e+00, 1.3466103438716175e+00, -1.8438471344336298e+00, -2.0952595273684760e+00, -7.7012218588605907e-01, 1.3705948670934771e+00};

    std::array<T, 8> reres{1.6867419926930389e+00, 1.5635267649025545e+01, 1.7030997128713221e+00, 2.2880149616855170e+00, -6.6737532774450159e-01, -5.4294479427715847e-01, -1.2185670369281292e+00, -2.2366901615818047e+00};

    std::array<T, 8> imres{1.1484897053630303e+00, 2.9235356194719746e+01, -4.8470591465484553e-01, 8.1442309859938877e-01, -1.6108318991995840e+00, -9.0484737739480448e-01, 7.8990385458658041e-01, 2.4137425589017183e+00};

    for(size_t i=0; i < re.size(); ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_kn(3, c), res, 1.0e-6) << i <<  " <- " << c << '\n';
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
//  using u_t = eve::underlying_type_t<T>;
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
