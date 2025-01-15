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
  auto pr = tts::prec<T>(1.0e-3, 1.0e-8);
  using c_t = kyosu::complex_t<T>;
  using a_t  = std::array<T, 6 >;
  a_t rx= { 0.0,  2.0,  0.0,  -1.0,  0.0, 0.0};
  a_t ix= { 0.0,  0.0,  0.0,   1.0, -1.0, 0.0};
  a_t ry= { 16.0, 3.0,  0.0,   0.0, -1.0, 0.0796};
  a_t iy= { 0.0,  0.0,  1.0,   1.0,  1.0, 0.0};
  a_t rz= { 16.0, 4.0,  0.0,   0.0,  0.0, 4.0};
  a_t iz= { 0.0,  0.0, -1.0,   0.0,  1.0, 0.0};

  a_t re = {3.1415926535898,  1.7255030280692, 0.42360654239699, 0.44660591677018, 0.36023392184473, 1.0284758090288};
  a_t im = {0.0,              0.0,             0.0,              0.70768352357515, 0.40348623401722, 0.0              };
  for(int i=0; i <= 5; ++i)
  {
      c_t x(rx[i], ix[i]);
      c_t y(ry[i], iy[i]);
      c_t z(rz[i], iz[i]);
      c_t r(re[i], im[i]);
      auto rr = kyosu::ellint_rg(x, y, z);
      TTS_RELATIVE_EQUAL(rr, r, pr);
  }
};
