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

    std::array<T, 10> reres{-1.9636104302526827e+41, -1.0554268283668887e+36, 6.7017263013768051e+10, -1.7015784833708476e+31, -1.0151625426581834e+40
        , 1.2635251338662279e+32, -1.8421720952281920e+20, 4.1135235740876322e+23, -4.0558105043998587e+01, -6.3240255029076477e+35};
    std::array<T, 10> imres{-6.7973248791507053e+40, -1.6878727168880668e+35, 1.4892104101040668e+11, -2.0851937688481058e+31, 2.3181031471337043e+40,
        5.3179705304830421e+32, -1.2145754380899834e+20, 1.5553955156953314e+24, 7.2736597971227624e+01, 3.5492040221662497e+35};
    for(int i=0; i < 10; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_in(3, c), res, 1.0e-7) << i <<  " <- " << c << '\n';
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
