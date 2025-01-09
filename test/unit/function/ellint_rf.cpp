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
  auto pr = tts::prec<T>(4.0e-2, 1.0e-8);
  using c_t = kyosu::complex_t<T>;
  using a_t  = std::array<T, 7 >;
  a_t rx= {-1.0,  1.0,  0.0, 2.0,  0.0, -1.0, 0.0};
  a_t ix= { 1.0,  0.0,  1.0, 0.0,  1.0,  1.0, 0.0};
  a_t ry= { 0.0,  2.0,  0.0, 3.0,  0.0,  0.0, 0.0};
  a_t iy= { 1.0, -0.0, -1.0, 0.0, -1.0,  1.0, 1.0};
  a_t rz= { 0.0,  0.0,  0.0, 4.0,  2.0,  1.0, 0.0};
  a_t iz= { 0.0,  0.0,  0.0, 0.0,  0.0, -1.0, 1.0};

  a_t re = {0.79612586584234,  1.3110287771461, 1.8540746773014, 0.58408284167715, 1.0441445654064, 0.93912050218619,   1.1107207345396};
  a_t im = {-1.2138566698365,  0.0,             0.0,             0.0,              0.0,             -0.5329625201863,  -1.1107207345396};
  if (sizeof(T) == 8)
  for(int i=0; i <= 6; ++i)
  {
    c_t x(rx[i], ix[i]);
    c_t y(ry[i], iy[i]);
    c_t z(rz[i], iz[i]);
    c_t r(re[i], im[i]);
    auto rr = kyosu::ellint_rf(x, y, z);
    TTS_RELATIVE_EQUAL(rr, r, pr);
  }
};
