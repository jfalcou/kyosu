//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_h12n over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};
    std::array<T, 16> reres2{-5.6487293158531979e-05, 6.5890828141819014e+01, -8.4284801947258066e-04, 3.6813584316790795e+01, 1.7088759302197115e-03, 1.5320007765665287e+00, 1.3354152761309773e-01, -9.2932925015189749e-01, 1.1165861949063943e-02, -5.3575707063653277e-01, 8.1391557866073649e-01, -4.5056659500341961e-03, 1.4237866007138228e+01, 2.4579837886114860e-03, 3.4408212753401202e+01, 1.7578714175771814e-04};
    std::array<T, 16> imres2{8.4060135972775416e-05, -2.4056185796796944e+02, -3.5348679634467821e-04, 1.1134050358938667e+00, -9.0902409344857694e-03, 4.9018709877144806e+00, -7.5824194390195195e-03, 7.8615436560341267e-01,-1.4480094011452358e+01, -2.2597037902118694e-01, -1.8946465279715725e+00, -2.8818132273240451e-02, -1.5187230562074436e+00, -1.1221552278486639e-03, 8.9402715175387669e+01, 2.3278894163732160e-04};
    std::array<T, 16> reres3{1.1208229382890835e-04, -1.9192184405276925e+02, -2.7777111106750833e-04, -5.4725122711374690e+00, -1.4097476196506266e-02, 2.0877738308485188e+00, -1.1138469058038176e-01, -1.1643936138223201e+00, 5.5934304776041695e-04, -1.5078142302454585e+00, -2.6264767828356361e-01, -4.6808412689629257e-02, 2.1456283474097195e+00, -8.0621291914483473e-04, 7.1868709602255961e+01, 3.2195900259589173e-04};
    std::array<T, 16> imres3{5.5716854320101858e-05, -1.7376967514127351e+01, 1.1801385263236690e-03, -2.4706540079280316e+01, 5.5684308316057988e-04, -1.6727014076828581e+00, -2.7872418293548179e-01, -3.4487011107518746e+00, -1.9077481501430970e+02, 9.1223988999494887e-01, -6.0375881450742841e-01, -7.5358656099016067e-03, -9.1744281816158395e+00, -3.5878042177064882e-03, -1.0866268820465949e+01, -1.7293470042642709e-04};

    std::vector<kyosu::complex_t<T>> h1s(6), h2s(6);
    for (int k = 0; k < 1; ++k)
    {
      auto c = kyosu::complex(re[k], im[k]);
      kyosu::cyl_bessel_h12n(3, c, std::span(h1s), std::span(h2s));
      int i = 0;
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_h1_0(c), h1s[0], tts::prec<T>()) << "i " << i  << " c "<< c << '\n';
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_h2_0(c), h2s[0], tts::prec<T>()) << "i " << i  << " c "<< c << '\n';
      i = 1;
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_h1_1(c), h1s[1], tts::prec<T>()) << "i " << i  << " c "<< c << '\n';
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_h2_1(c), h2s[1], tts::prec<T>()) << "i " << i  << " c "<< c << '\n';
      i = 2;
      auto ref2 =  kyosu::complex_t<T>(reres2[k], imres2[k]);
      TTS_RELATIVE_EQUAL(ref2, h1s[2], tts::prec<T>()) << "i " << i  << " c "<< c << '\n';
      i = 3;
      auto ref3 =  kyosu::complex_t<T>(reres3[k], imres3[k]);
      TTS_RELATIVE_EQUAL(ref3, h1s[3], tts::prec<T>()) << "i " << i  << " c "<< c << '\n';

    }
  }
};

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_h12n over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10),
                              tts::randoms(-10,10)
                             )
              )
<typename T>(T a0, T a1)
{
  using u_t = eve::underlying_type_t<T>;
  auto z =  kyosu::complex(a0, a1);
  auto zer =   kyosu::complex(T(0), T(0));
  {
    auto iminf=   kyosu::complex(T(0), eve::minf(eve::as<T>()));
    for(int i=0; i <10 ; ++i)
    {
      auto h1nz = kyosu::cyl_bessel_h1n(i, z);
      auto yzer =  kyosu::cyl_bessel_h1n(i, zer);
      TTS_IEEE_EQUAL(yzer, i ? iminf : kyosu::inc(iminf));
      TTS_IEEE_EQUAL(h1nz, eve::sign_alternate(u_t(i))*kyosu::cyl_bessel_h1n(-i, z)) << i << '\n';
    }
  }
 {
    auto iinf=   kyosu::complex(T(0), eve::inf(eve::as<T>()));
    for(int i=0; i <10 ; ++i)
    {
      auto h1nz = kyosu::cyl_bessel_h2n(i, z);
      auto yzer =  kyosu::cyl_bessel_h2n(i, zer);
      TTS_IEEE_EQUAL(yzer, i ? iinf : kyosu::inc(iinf));
      TTS_IEEE_EQUAL(h1nz, eve::sign_alternate(u_t(i))*kyosu::cyl_bessel_h2n(-i, z)) << i << '\n';
    }
  }
};
