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

TTS_CASE_TPL ( "Check hyper 0f2"
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  if constexpr(sizeof(T) == 8)
  {
    auto pr = tts::prec<T>(4.0e-3, 1.0e-8);
    using r_t = kyosu::cayley_dickson<T, 2>;
    r_t I = r_t(0.0, 1.0);
    auto cinf = kyosu::cinf(eve::as<r_t>());
    auto fnan = kyosu::fnan(eve::as<r_t>());
    r_t res[] = {cinf,
                 cinf,
                 r_t(1.2605622498372,0),
                 r_t(1.2605622498372,0),
                 r_t(1.217152359520, 0.541355499156),
                 cinf,
                 cinf,
                 r_t(0.8709320903800835, 1.595611888000411100),
                 r_t(-0.15510128560640311, 0),
                 r_t(99.114025759178851, 0),
                 r_t(-0.594262517368413, 0),
                 r_t(1.5663856354621291, 0),
                 r_t(1.2476782459109788, -0.263661379811756292),
                 r_t(0.7602728919571687, 0),
                 r_t(1.00095707738546121, -0.00288656734228238),
                 r_t(1.00160841448086852, -0.00487045948488402),
                 fnan};

    r_t r(cinf);
    std::cout << std::setprecision(15);
    // a0 a1 or b0 negatives integers
    r = kyosu::hypergeometric(0.5, kumi::tuple{}, kumi::tuple{-2.0, 1.0});
    TTS_RELATIVE_EQUAL(r, res[0], pr);
    r = kyosu::hypergeometric(0.5, kumi::tuple{}, kumi::tuple{1.0, -2.0});
    TTS_RELATIVE_EQUAL(r, res[1], pr);
    r = kyosu::hypergeometric(0.5, kumi::tuple{}, kumi::tuple{2.0, 1.0});
    TTS_RELATIVE_EQUAL(r, res[2], pr);
    r = kyosu::hypergeometric(0.5, kumi::tuple{}, kumi::tuple{1.0, 2.0});
    TTS_RELATIVE_EQUAL(r, res[3], pr);
    r = kyosu::hypergeometric(r_t(0.5, 1.0), kumi::tuple{}, kumi::tuple{1.0, 2.0});
    TTS_RELATIVE_EQUAL(r, res[4], pr);
    r = kyosu::hypergeometric(0.5, kumi::tuple{}, kumi::tuple{1.5, -2.0});
    TTS_RELATIVE_EQUAL(r, res[5], pr);
    r = kyosu::hypergeometric(0.5, kumi::tuple{}, kumi::tuple{-1.0, -2.0});
    TTS_RELATIVE_EQUAL(r, res[6], pr);
    r = kyosu::hypergeometric(0.5+3*I, kumi::tuple{}, kumi::tuple{2.0, 1.0});
    TTS_RELATIVE_EQUAL(r, res[7], pr);
    r = kyosu::hypergeometric(-3.0, kumi::tuple{}, kumi::tuple{2.0, 1.0});
    TTS_RELATIVE_EQUAL(r, res[8], pr);
    r = kyosu::hypergeometric(30.0, kumi::tuple{}, kumi::tuple{2.0, 1.0});
    TTS_RELATIVE_EQUAL(r, res[9], pr);
    r = kyosu::hypergeometric(-5.0, kumi::tuple{}, kumi::tuple{2.0, 1.0});
    TTS_RELATIVE_EQUAL(r, res[10], pr);
    r = kyosu::hypergeometric(1.04, kumi::tuple{}, kumi::tuple{1.0, 2.0});
    TTS_RELATIVE_EQUAL(r, res[11], pr);
    r = kyosu::hypergeometric(0.96, kumi::tuple{}, kumi::tuple{1.0+I, 2.0});
    TTS_RELATIVE_EQUAL(r, res[12], pr);
    r = kyosu::hypergeometric(-0.5, kumi::tuple{}, kumi::tuple{1.0, 2.0});
    TTS_RELATIVE_EQUAL(r, res[13], pr);
    r = kyosu::hypergeometric(0.4-1.2*I, kumi::tuple{}, kumi::tuple{-20.4, -20.4});
    TTS_RELATIVE_EQUAL(r, res[14], pr);
    r = kyosu::hypergeometric(0.4-1.2*I, kumi::tuple{}, kumi::tuple{-20.4, -12.1});
    TTS_RELATIVE_EQUAL(r, res[15], pr);

    r = kyosu::hypergeometric(cinf, kumi::tuple{}, kumi::tuple{-20.4, -12.1});
    TTS_RELATIVE_EQUAL(r, res[16], pr);
   }
};
