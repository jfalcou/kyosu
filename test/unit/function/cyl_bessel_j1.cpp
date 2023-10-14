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
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j1(c), res, 1.0e-7) << i <<  " <- " << c << '\n';
    }
  }
};

// TTS_CASE_WITH ( "Check kyosu::abs over complex"
//               , kyosu::real_types
//               , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
//               )
// (auto r, auto i)
// {
//   TTS_EQUAL(kyosu::abs(kyosu::complex(r,i)), eve::hypot(r, i));
// };

// TTS_CASE_WITH ( "Check kyosu::abs over quaternion"
//               , kyosu::real_types
//               , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               )
//               )
// <typename T>(T r, T i, T j, T k)
// {
//   using type = kyosu::quaternion_t<T>;
//   TTS_EQUAL(kyosu::abs(type(r,i,j,k)), eve::hypot(r, i, j, k));
// };
