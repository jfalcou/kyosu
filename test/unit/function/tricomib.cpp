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
    auto cinf = kyosu::cinf(eve::as<r_t>());
    r_t res[] = {r_t(-0.670482709790073, -0.425168331587636328),
                 r_t(0.1704827097900732, 0.4251683315876363284391),
                 r_t(0.0397586451049633, -0.21258416579381816421),
                 r_t(0.596347362323194, 0.0),
                 r_t(10.93582915778848, 0.0),
                 r_t(-0.2707662554910, -0.021167884792604296731),
                 r_t(-0.11314702047341, -0.00014262808581531501620860)
    };
    r_t r(cinf);
 //    r = kyosu::tricomi(-2.0, 1.0, 1.0);
//     TTS_RELATIVE_EQUAL(r, res[0], pr);
    r = kyosu::tricomi(-2.0, 2.0, 2.0);
    TTS_RELATIVE_EQUAL(r, res[1], pr);
//     r = kyosu::tricomi(-2.0, 3.0, 3.0);
//     TTS_RELATIVE_EQUAL(r, res[2], pr);
//     r = kyosu::tricomi(1.0, 1.0, 1.0);
//     TTS_RELATIVE_EQUAL(r, res[3], pr);
//     r = kyosu::tricomi(1.0e-5, 1.0, 1.0);
//     TTS_RELATIVE_EQUAL(r, res[4], pr);
//     r = kyosu::tricomi(-5.0, 1.0, 1.0);
//     TTS_RELATIVE_EQUAL(r, res[5], pr);
//     r = kyosu::tricomi(-10.0, 1.0, 1.0);
//     TTS_RELATIVE_EQUAL(r, res[6], pr);


  }
};
