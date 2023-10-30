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
  using e_t = eve::element_type_t<T>;
  if constexpr(sizeof(e_t) == 8)
  {
    std::cout.precision(17);
    std::array<T, 10> re{ -9.8403264736233908e+01, 8.6287324687322851e+01, 2.8677183208357349e+01, 7.5642931882481321e+01, 9.6351793077594323e+01
        , -7.8716695947540288e+01, -5.0019457963533974e+01, 5.9030075032843811e+01, -7.5596124248257235e+00, 8.5810875418338028e+01};
    std::array<T, 10> im{-1.9271037994246587e+01, 7.9043790847200569e+01, -3.0599555605285602e+01, -7.1720588923445590e+01, -6.1110206702938363e+01
        , 9.0167523214068439e+01, -7.0131934820406244e+01, -9.3405497312943496e+01, 8.3431692318213322e+01, -4.1557438097347173e+01};

    std::array<T, 10> reres{3.0094177278540167e+06, -6.8058089697014938e+32, -3.8806283458664719e+10, -8.6565181213118240e+28, 1.2915079982169630e+25,
        -9.3925711342553668e+36, 6.4595726071319036e+28, 1.1238442153777222e+39, -7.0123433800633681e+34, -1.9060735303763808e+16};
    std::array<T, 10> imres{8.8185850069141667e+06, -3.8848970122848989e+32, 1.1905919032156870e+12, -5.4098751798106477e+29, 4.2914274806719309e+23,
        -5.1646555066948327e+37, -1.0459530606430648e+29, 8.2050979033727447e+38, 2.4737508957685513e+34, 4.1393451863209432e+16};
    for(int i=0; i < 10; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::log(kyosu::complex(reres[i], imres[i]));
      TTS_RELATIVE_EQUAL(kyosu::cyl_lbessel_j1(c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }
  std::cout.precision(17);
  std::array<T, 8> re{2.175102683907268e+00, 3.007738475083643e-01, 3.571791197760752e+00, 1.916834892035037e+00, 2.309329011574615e+00, 1.116302757926106e+00, 3.454188251414261e+00, 2.504516854443353e+00};
  std::array<T, 8> im{  3.008362577802520e+00, 3.733804275914350e+00, 2.988312632706299e+00, 4.411110052057489e+00, 3.055249958745497e+00, 2.508994160634028e+00, 3.100976745146938e-01, 3.854880352108083e+00};

  std::array<T, 8> reres{3.6097545599299043e+00, 2.0607036224436954e+00, -2.1724057594208968e-01, 1.3644664632775582e+01, 3.5380568884368788e+00, 2.1507545829381751e+00, 1.5764037998430128e-01, 6.2619292962097814e+00};
  std::array<T, 8> imres{-1.3891357467781533e+00, 7.3810832876707710e+00, -3.4818290031753225e+00, -2.4845686655182946e+00, -1.8826359832772270e+00, 1.3851339474357725e+00, -1.3157891968242472e-01, -5.2738074786282327e+00};
  for(int i=0; i < 8; ++i)
  {
    auto c = kyosu::complex(re[i], im[i]);
    auto res = kyosu::log(kyosu::complex(reres[i], imres[i]));
    double tol = (sizeof(e_t) == 4) ? 1.e-3 :1.e-7;
    TTS_RELATIVE_EQUAL(kyosu::cyl_lbessel_j1(c), res, tol) << i <<  " <- " << c << '\n';
  }
};

// TTS_CASE_WITH ( "Check kyosu::cyl_lbessel_j1 over real"
//               , kyosu::real_types
//               , tts::generate(tts::randoms(-10,10),
//                               tts::randoms(-10,10)
//                              )
//               )
// <typename T>(T a0, T a1)
// {
//   if constexpr(sizeof(T) == 8)
//   {
//     using e_t = eve::element_type_t<T>;
//     double tol = (sizeof(e_t) == 4) ? 1.e-3 :1.e-7;
//     auto c =  kyosu::complex(a0, a1);
//     auto cb=  kyosu::conj(c);
//     auto cm=  -c;
//     using kyosu::cyl_lbessel_j1;
//     using kyosu::cyl_bessel_j1;
//     auto lj1c = cyl_lbessel_j1(c);
//     auto logj1c = kyosu::log(cyl_bessel_j1(c));
//     TTS_RELATIVE_EQUAL(lj1c, logj1c, tol) << "c " << c << "\n";

//     auto lj1cb = cyl_lbessel_j1(cb);
//     auto logj1cb = kyosu::log(cyl_bessel_j1(cb));
//     TTS_RELATIVE_EQUAL(lj1cb, logj1cb, tol) << "c " << c << "\n";

//     auto lj1cm = cyl_lbessel_j1(cm);
//     auto logj1cm = kyosu::log(cyl_bessel_j1(cm));
//     TTS_RELATIVE_EQUAL(lj1cm, logj1cm, tol) << "c " << c << "\n";
//     auto z =   kyosu::complex(T(0), T(0));
//     TTS_IEEE_EQUAL(cyl_lbessel_j1(z), kyosu::complex(eve::minf(eve::as<e_t>())));
//   }
// };