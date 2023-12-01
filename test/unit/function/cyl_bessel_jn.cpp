//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_jn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {

    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};

    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};

    std::array<T, 16> reres{-9.2945378069946427e-01, -5.5654463652021580e-01, -1.3762005408985431e-01, -2.0629599116397824e-02, -1.7848558532356923e-03, -6.7901907189656606e-05, -4.4441290433078812e-07, 4.4739084830719597e-10, 1.5858465157002424e-15, 3.9133464867901946e-10, -2.6124248491522775e-06, -1.4351523349435534e-04, -2.2467942887287522e-03, -1.6383095767178162e-02, -5.2590310312067429e-02, 1.3655007723611573e-01};

    std::array<T, 16> imres{-4.3261812621784550e+00, 7.2249881349373990e-01, -7.5392360584650292e-02, 2.4145390271178412e-03, 4.5787959406437995e-04, -5.0158069394027434e-05, 1.0072715695591406e-06, -3.6299101757673117e-10, 0.0000000000000000e+00, 8.6035082077564487e-09, -3.4022089623455758e-06, 1.4465906663362226e-04, -2.6426081339425084e-03, 2.9241512426902948e-02, -2.2181516452594596e-01, 1.2204264468291262e+00};

    for(int i=0; i < 16; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_jn(10, c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_jn over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T a0, T a1)
{
  using u_t = eve::underlying_type_t<T>;
  auto c =  kyosu::complex(a0, a1);
  auto cb=  kyosu::conj(c);
  auto cm=  -c;
  auto cr=  kyosu::complex(a0);
  auto ci=  kyosu::complex(T(0), a1);
  auto zer =   kyosu::complex(T(0), T(0));
  auto one =   kyosu::complex(T(1), T(0));

  using kyosu::cyl_bessel_jn;

  for(int i=0; i < 10 ; ++i)
  {
    auto jnc = cyl_bessel_jn(i, c);
    TTS_IEEE_EQUAL(jnc, eve::sign_alternate(u_t(i))*cyl_bessel_jn(i, cm)) << "c " << c << "\n";
    TTS_IEEE_EQUAL(jnc, kyosu::conj(cyl_bessel_jn(i, cb)));
    TTS_EXPECT(eve::all(kyosu::is_real(cr)));
    TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
    TTS_IEEE_EQUAL(cyl_bessel_jn(i, zer), i ? zer : one) << "i " << i << '\n';
    TTS_IEEE_EQUAL(jnc, eve::sign_alternate(u_t(i))*cyl_bessel_jn(-i, c)) << i << '\n';
  }
};
