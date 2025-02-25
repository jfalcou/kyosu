//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <iomanip>
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <eve/wide.hpp>
#include <iostream>

TTS_CASE_TPL ( "Check hyper 2F1"
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  if constexpr(sizeof(T) == 8)
  {
    auto pr = tts::prec<T>(4.0e-3, 1.0e-8);
    using r_t = kyosu::cayley_dickson<T, 2>;
    r_t I = r_t(0.0, 1.0);
    std::cout << I << std::endl;
//    std::cout << tts::name(r_t()) << std::endl;
    auto nan = eve::nan(eve::as<T>());
    r_t res[] = {r_t(1.34285714285714, 0), r_t(1.34285714285714), kyosu::cinf(eve::as<r_t>()), kyosu::cinf(eve::as<r_t>()), r_t(1.41666666666667,0), r_t(1.53571428571429,0),
                 r_t(0.666666666666667,0), r_t(1.43805509807655,0), r_t(0.399423339498422,0), r_t(-0.0945434530050565,-0.0128699542349234),
                 r_t(0.292430451098607,0), r_t(4.26012617974386,-2.13613053370195), r_t(3.25898889914176,0), r_t(0.784430166457414,0), r_t(-332.644427109075,-224.988297978431),
                 r_t(23.6353087752502,25.8503131412853), r_t(-210.714285714285,-5.1610115106924e-14), r_t(-20190.0135825192,0), r_t(-20236927.9546885,1.15423160805968e-100),
                 r_t(1.0, 0.0), r_t(-1.0, 0.0)};
    r_t r(nan);
    // a0 a1 or b0 negatives integers
    r = kyosu::hypergeometric(0.5, kumi::tuple{-2.0, 1.0}, kumi::tuple{-3.5});
    TTS_RELATIVE_EQUAL(r, res[0], pr);
    r =  kyosu:: hypergeometric(0.5, kumi::tuple{1.0, -2.0}, kumi::tuple{-3.5});
    TTS_RELATIVE_EQUAL(r, res[1], pr);
    r = kyosu::hypergeometric(0.5, kumi::tuple{2.0,1.0}, kumi::tuple{-3.0});
    TTS_RELATIVE_EQUAL(r, res[2], pr);
    r =  kyosu:: hypergeometric(0.5, kumi::tuple{1.0, 2.0}, kumi::tuple{-3.0});
    TTS_RELATIVE_EQUAL(r, res[3], pr);
    r = kyosu::hypergeometric(0.5, kumi::tuple{-2.0,1.0}, kumi::tuple{-3.0});
    TTS_RELATIVE_EQUAL(r, res[4], pr);
    r =  kyosu:: hypergeometric(0.5, kumi::tuple{1.5, -2.0}, kumi::tuple{-3.5});
    TTS_RELATIVE_EQUAL(r, res[5], pr);
    r =  kyosu:: hypergeometric(0.5, kumi::tuple{-1.0, -2.0}, kumi::tuple{-3.0});
    TTS_RELATIVE_EQUAL(r, res[6], pr);
    r =  kyosu::hypergeometric(0.5, kumi::tuple{2.0, 1.0}, kumi::tuple{3.5});
    TTS_RELATIVE_EQUAL(r, res[7], pr);
    r =  kyosu::hypergeometric(-3.0, kumi::tuple{2.0, 1.0}, kumi::tuple{3.5});
    TTS_RELATIVE_EQUAL(r, res[8], pr);
    r =  kyosu::hypergeometric(30.0, kumi::tuple{1.0, 2.0}, kumi::tuple{3.5});
    TTS_RELATIVE_EQUAL(r, res[9], pr);
    r =  kyosu::hypergeometric(-5.0, kumi::tuple{2.0, 1.0}, kumi::tuple{3.5});
    TTS_RELATIVE_EQUAL(r, res[10], pr);
    r =  kyosu::hypergeometric(1.04, kumi::tuple{1.0, 2.0}, kumi::tuple{3.5});
    TTS_RELATIVE_EQUAL(r, res[11], pr);
    r =  kyosu::hypergeometric(0.96, kumi::tuple{1.0, 2.0}, kumi::tuple{3.5});
    TTS_RELATIVE_EQUAL(r, res[12], pr);
    r =  kyosu::hypergeometric(-0.5, kumi::tuple{1.0, 2.0}, kumi::tuple{3.5});
    TTS_RELATIVE_EQUAL(r, res[13], pr);
    r =  kyosu::hypergeometric(0.4-1.2*I, kumi::tuple{-20.4, -20.4}, kumi::tuple{-20.4});
    TTS_RELATIVE_EQUAL(r, res[14], pr);
    r =  kyosu::hypergeometric(0.4-1.2*I, kumi::tuple{-20.4, -12.1}, kumi::tuple{-20.4});
    TTS_RELATIVE_EQUAL(r, res[15], pr);
    r =  kyosu::hypergeometric(1.04, kumi::tuple{1.0, -2.5}, kumi::tuple{-3.5});
    TTS_RELATIVE_EQUAL(r, res[16], pr);
    r =  kyosu::hypergeometric(-1.0, kumi::tuple{-10.8, -10.8}, kumi::tuple{-0.4});
    TTS_RELATIVE_EQUAL(r, res[17], pr);
    r =  kyosu::hypergeometric(1.000001-1e-307*I, kumi::tuple{-10.4, -10.4}, kumi::tuple{-4.4});
    TTS_RELATIVE_EQUAL(r, res[18], pr);
    r =  kyosu::hypergeometric(0.25, kumi::tuple{0.0, 2.0}, kumi::tuple{1.5});
    TTS_RELATIVE_EQUAL(r, res[19], pr);
    r =  kyosu::hypergeometric(1.0, kumi::tuple{-3.0, 5.0}, kumi::tuple{1.5});
    TTS_RELATIVE_EQUAL(r, res[20], pr);


  }
  TTS_EQUAL(0, 0);
};
