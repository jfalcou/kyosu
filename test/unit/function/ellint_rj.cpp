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
// the values tested are those contained in the original Carlson article
// computation of elliptic integrals, Bille C. Carlson arXiv:math/9409227

TTS_CASE_TPL ( "Check ellint_rj over complex"
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(4.0e-3, 1.0e-8);
  using c_t = kyosu::complex_t<T>;
  using a_t  = std::array<T, 8 >;
  a_t rx= { 0.0,   2.0,   2.0,  0.0, -1.0,  0.0, -1.0, -1.0};
  a_t ix= { 0.0,   0.0,   0.0,  1.0,  1.0,  1.0,  1.0,  1.0};
  a_t ry= { 1.0,   3.0,   3.0,  0.0, -1.0,  0.0, -1.0, -2.0};
  a_t iy= { 0.0,   0.0,   0.0, -1.0, -1.0, -1.0, -1.0, -1.0};
  a_t rz= { 2.0,   4.0,   4.0,  0.0,  1.0,  0.0,  1.0,  0.0};
  a_t iz= { 0.0,   0.0,   0.0,  0.0,  0.0,  0.0,  0.0, -1.0};
  a_t rp= { 3.0,   5.0,  -1.0,  2.0,  2.0,  1.0, -3.0, -1.0};
  a_t ip= { 0.0,   0.0,   1.0,  0.0,  0.0, -1.0,  1.0,  1.0};
  a_t re = {0.77688623778582, 0.14297579667157,  0.13613945827771, 1.6490011662711, 0.94148358841220, 1.8260115229009, -0.61127970812028 , 1.8249027393704};
  a_t im = {0.0,              0.0,              -0.38207561624427, 0.0,             0.0             , 1.2290661908643, -1.0684038390007,  -1.2218475784827};
  for(int i=0; i < 8; ++i)
  {
    c_t x(rx[i], ix[i]);
    c_t y(ry[i], iy[i]);
    c_t z(rz[i], iz[i]);
    c_t p(rp[i], ip[i]);
    c_t r(re[i], im[i]);
    auto rr = kyosu::ellint_rj(x, y, z, p);
    TTS_RELATIVE_EQUAL(rr, r, pr);
  }
};
