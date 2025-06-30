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

TTS_CASE_TPL ( "Check tricomi "
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
    r_t res[] = {r_t(0.263649601604, 0.063890574166552),
                 r_t(0.4213692292880, 0.0),
                 r_t(0.075192911520, 0.0),
                 r_t(0.010338915008, 0.08232684012981332521971),
                 r_t(4.4195931497672e18, -1.1367863689312e19),
                 r_t(-0.454219904863173, -3.141592653589793238)
    };
    r_t r(cinf);
    std::cout << std::setprecision(15);
    r = kyosu::tricomi(2.0, 1, I);
    TTS_RELATIVE_EQUAL(r, res[0], pr);
    r = kyosu::tricomi(2.0, 1.0, 1.5);
    TTS_RELATIVE_EQUAL(r, res[1], pr);
    r = kyosu::tricomi(0.5, 2.0, -1.4);
    TTS_RELATIVE_EQUAL(r, res[2], pr);
    r = kyosu::tricomi(0.5, 1.0, 12*I);
    TTS_RELATIVE_EQUAL(r, res[3], pr);
    r = kyosu::tricomi(0.4-1.2*I, -20.4, -20.4);
    TTS_RELATIVE_EQUAL(r, res[4], pr);
    r = kyosu::tricomi(1.0, 1.0, -2);
    TTS_RELATIVE_EQUAL(r, res[5], pr);
  }
};
