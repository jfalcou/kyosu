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
    auto pr = tts::prec<T>(4.0e-3, 1.0e-15);
    using r_t = kyosu::cayley_dickson<T, 2>;
    auto cinf = kyosu::cinf(eve::as<r_t>());
    r_t res[] = {r_t(-0.670482709790073, -0.425168331587636328),
                 r_t(0.357932),
                 r_t(0.03975864510496, -0.2125841657938181642),
                 r_t(0.0397586451049633, -0.21258416579381816421),
                 r_t(0.596347362323194, 0.0),
                 r_t(10.93582915778848, 0.0),
                 r_t(-0.2707662554910, -0.021167884792604296731),
                 r_t(0.181761874151898, 0.0),
                 r_t(0.680920590299878, 0.0),
                 r_t(0.277406605653042, 0.0),
                 r_t(0.138671383111777, 0.0),
                 r_t(-0.05491954836832, 0.070861388597939388073)
    };
    r_t r(cinf);
    r = kyosu::tricomi(-2.0, 1.0, 1.0);
    TTS_RELATIVE_EQUAL(r, res[0], pr);
    r = kyosu::tricomi(1.0, 1.5, 1.0);
    TTS_RELATIVE_EQUAL(r, res[1], pr);
    r = kyosu::tricomi(-2.0, 3.0, 3.0);
    TTS_RELATIVE_EQUAL(r, res[2], pr);
    r = kyosu::tricomi(1.0, 1.0, 1.0);
    TTS_RELATIVE_EQUAL(r, res[4], pr);
    r = kyosu::tricomi(1.0e-5, 1.0, 1.0);
    TTS_RELATIVE_EQUAL(r, res[5], pr);
    r = kyosu::tricomi(-5.0, 1.0, 1.0);
    TTS_RELATIVE_EQUAL(r, res[6], pr);
    r = kyosu::tricomi(-10.0, 1.0, 1.0);
    TTS_RELATIVE_EQUAL(r, res[6], pr);
    r = kyosu::tricomi(2.0, 1.5, 1.0);
    TTS_RELATIVE_EQUAL(r, res[7], pr);
    r = kyosu::tricomi(1.0, 1.5, 2.0);
    TTS_RELATIVE_EQUAL(r, res[8], pr);
    r = kyosu::tricomi(2.0, 1.5, 2.0);
    TTS_RELATIVE_EQUAL(r, res[9], pr);
    r = kyosu::tricomi(2.0, 2.0, 2.0);
    TTS_RELATIVE_EQUAL(r, res[10], pr);
    r = kyosu::tricomi(-2.0, 4.0, 4.0);
    TTS_RELATIVE_EQUAL(r, res[11], pr);

  }
};
// sum_(k=0)^20 ((1.5)_k (\u03c8(1.5 + k) - \u03c8(1 + k) - \u03c8(1 + k)) 1^k)/((k + 1 - 1)! k!)\u2248-0.3172090633360333543575118713021572347289
// sum_(k=0)^20 ((1.5)_k (\u03c8(1.5 + k) - \u03c8(
