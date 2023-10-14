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

    std::array<T, 10> reres{-3.3279158735087640e+06, 6.7446373092398792e+32, 1.0973422267168294e+11, 6.9510412682541761e+28, -1.2657523599731811e+25,
        8.0429582124849094e+36, -5.9430267579521807e+28, -1.0741846420111567e+39, 6.6950456879149885e+34, 2.0245919743884628e+16};
    std::array<T, 10> imres{-8.6289796115820184e+06, 3.6264735895350172e+32, -1.1056118662675706e+12, 5.2905159458975805e+29, -7.9797425680943093e+23,
        5.0551834834322169e+37, 1.0236118318065309e+29, -8.1681100953492296e+38, -2.3290495380992445e+34, -3.9909835121233848e+16};
    for(int i=0; i < 10; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_jn(3, c), res, 1.0e-7) << i <<  " <- " << c << '\n';
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
