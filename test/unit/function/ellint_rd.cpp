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

TTS_CASE_TPL ( "Check ellint_rj over complex"
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(1.0e-3, 1.0e-8);
  using c_t = kyosu::complex_t<T>;
  using a_t  = std::array<T, 6 >;
  a_t rx= { 0.0,   2.0,  0.0,   0.0,  0.0 , -2.0};
  a_t ix= { 0.0,   0.0,  1.0,   0.0,  0.0 , -1.0};
  a_t ry= { 2.0,   3.0,  0.0,   0.0, -1.0 ,  0.0};
  a_t iy= { 0.0,   0.0, -1.0,   1.0,  1.0 , -1.0};
  a_t rz= { 1.0,   4.0,  2.0,   0.0,  0.0 , -1.0};
  a_t iz= { 0.0,   0.0,  0.0,  -1.0,  1.0 ,  1.0};
  a_t re = {1.7972103521034, 0.16510527294261, 0.65933854154220, 1.2708196271910, -1.8577235439239,   1.8249027393704};
  a_t im = {0.0,             0.0,              0.0,              2.7811120159521, -0.96193450888839, -1.2218475784827};
  for(int i=0; i < 6; ++i)
  {
    c_t x(rx[i], ix[i]);
    c_t y(ry[i], iy[i]);
    c_t z(rz[i], iz[i]);
    c_t r(re[i], im[i]);
    auto rr = kyosu::ellint_rd(x, y, z);
    TTS_RELATIVE_EQUAL(rr, r, pr);
  }
};
