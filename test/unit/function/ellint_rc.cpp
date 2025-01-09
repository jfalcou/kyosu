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

TTS_CASE_TPL ( "Check ellint_rf over complex"
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(4.0e-3, 1.0e-8);
  using c_t = kyosu::complex_t<T>;
  using a_t  = std::array<T, 6 >;
  a_t rx= { 0.0,   2.25,  0.0,  0.0, 0.25,  0.0,  0.0};
  a_t ix= { 0.0,   0.0,   0.0, -1.0,  0.0,  1.0,  0.0};
  a_t ry= { 0.25,  2.0,   0.0,  0.0, -2.0, -1.0,  0.0};
  a_t iy= { 0.0,   0.0,   1.0,  1.0,  0.0,  0.0,  0.0};
  a_t re = {3.1415926535898,  0.69314718055995, 1.1107207345396,  1.2260849569072,   0.23104906018665, 0.77778596920447};
  a_t im = {0.0,              0.0,              -1.1107207345396, -0.34471136988768, 0.0,              0.19832484993429};
  if (sizeof(T) == 8)
  for(int i=4; i <= 6; ++i)
  {
    c_t x(rx[i], ix[i]);
    c_t y(ry[i], iy[i]);
    c_t r(re[i], im[i]);
    auto rr = kyosu::ellint_rc(x, y);
    TTS_RELATIVE_EQUAL(rr, r, pr);
  }
};
