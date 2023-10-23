//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::abs over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::cout.precision(17);
    std::array<T, 8> re{-4.2214088790474964e+00, -7.8055061036477191e-01, 3.4677730339081023e+00, -3.5357366395596843e+00, 2.6849636588863888e+00, 4.1415226198517496e+00, -4.3623200824031505e+00, 1.0341209529062589e-01};

    std::array<T, 8> im{1.0956977560286330e+00, -7.5270747683236494e-01, -2.3663854475056922e+00, 2.1367696130628167e-01, 3.8676287626125005e+00, 1.2360189302485036e+00, -1.6272444761141791e+00, 2.3032771326096082e+00};

    std::array<T, 8> reres{-1.4430835201379668e+00, 1.9196191347820878e-02, -2.2546300709067921e+00, -1.8495328601568108e+00, -6.9308023933848761e-01, 6.6553153864637693e-01, 1.3620695910489697e+00, -1.8567185218040287e-02};

    std::array<T, 8> imres{4.3199672659258121e+00, -1.8483194393765133e-02, -9.7213268648765250e-01, 4.9949262720449961e-01, -1.4530419537731945e+00, 4.1725828994086056e+00, -5.4440977364260119e+00, -1.8030965329489912e-01};
    for(size_t i=0; i < re.size(); ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_in(3, c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }


  using e_t = eve::element_type_t<T>;
  std::array<T, 8> re{2.0709361678462956e+00, 5.1596138276942927e-01, -2.2170102176897553e+00, -1.4369438543103081e+00, -7.6957829009966450e-01, -1.7101763208939635e+00, 3.4657238297437165e-01, -2.1018021021318942e+00};

  std::array<T, 8> im{-2.9011812121960689e-02, 7.3607208974466765e-01, 2.2280446499823059e+00, -5.3739618318618343e-01, -4.5166849463082692e-01, -1.2572863733973971e+00, 2.4895675798384671e+00, 1.0768334172105560e+00};

  std::array<T, 8> reres{2.4005271979790385e-01, -1.4531644474457872e-02, 6.6035352188283469e-01, -3.2931456259011171e-02, 9.7985905063145175e-04, 1.2221115376039396e-01, -6.5446528495838319e-02, 4.0833307902227237e-02};

  std::array<T, 8> imres{-1.1811642368037799e-02, 3.1838598500426520e-03, 1.1009794439809784e-01, -7.7305063502964677e-02, -1.5136401459191786e-02, -1.8055180597316350e-01, -2.1326769783365454e-01, 3.3490504426093021e-01};

  for(size_t i=0; i < re.size(); ++i)
  {
    auto c = kyosu::complex(re[i], im[i]);
    auto res = kyosu::complex(reres[i], imres[i]);
    double tol = (sizeof(e_t) == 4) ? 1.e-3 :1.e-7;
    TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_in(3, c), res, tol) << i <<  " <- " << c << '\n';
  }
};


TTS_CASE_WITH ( "Check kyosu::abs over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T a0, T a1)
{
  auto c =  kyosu::complex(a0, a1);
  auto cb=  kyosu::conj(c);
  auto cm=  -c;
  auto cr=  kyosu::complex(a0);
  auto ci=  kyosu::complex(T(0), a1);
  using kyosu::cyl_bessel_in;
  auto inc = cyl_bessel_in(3, c);
  TTS_IEEE_EQUAL(inc, -cyl_bessel_in(3, cm));
  TTS_IEEE_EQUAL(inc, kyosu::conj(cyl_bessel_in(3, cb)));
  TTS_EXPECT(eve::all(kyosu::is_real(cr)));
  TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
  auto z =   kyosu::complex(T(0), T(0));
  TTS_IEEE_EQUAL(cyl_bessel_in(3, z), z);
};
