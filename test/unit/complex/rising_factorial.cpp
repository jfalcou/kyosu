//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <complex>

TTS_CASE_WITH ( "Check behavior of rising_factorial on wide"
              , kyosu::real_types
              , tts::generate ( tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t = T;
  using z_t = kyosu::as_complex_t<T>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);

  auto rf =  [](auto x,  auto a){return kyosu::tgamma(a+x)/kyosu::tgamma(x); };

  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, b) , rf(a, b),1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, z_t(2, 0)), a*(a+1), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, z_t(3, 0)), a*(a+1)*(a+2),  1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(kyosu::abs(a0), b)   , rf(kyosu::abs(a0), b), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(-kyosu::abs(a0), b)   , rf(-kyosu::abs(a0), b), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(b, kyosu::abs(a0))   ,  rf(b, kyosu::abs(a0)), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, 3u)   , kyosu::rising_factorial(a, e_t(3)),  1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, 2u)   , kyosu::rising_factorial(a, e_t(2)),  1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, -2)   , kyosu::rising_factorial(a, e_t(-2)),  1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(z_t(0, 0), z_t(0, 0)), z_t(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(z_t(1, 0), z_t(0, 0)), z_t(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(z_t(1, 3), z_t(0, 0)), z_t(1, 0), 1.0e-5);

  using eve::as;
  auto inf = eve::inf(as<e_t>());
  auto minf = eve::minf(as<e_t>());
  auto nan = eve::nan(as<e_t>());

  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(z_t(inf, 0), z_t(0, 0)), z_t(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(z_t(minf, 0), z_t(0, 0)), z_t(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(z_t(nan, 0), z_t(0, 0)), z_t(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(z_t(nan, 1), z_t(0, 0)), z_t(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(z_t(0, 0),  z_t(0, 0)), z_t(1, 0), 1.0e-5);
  z_t i(0, 1);
  z_t o(1, 0);
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial(i, i),      z_t(0.133408195318916183621, +0.06139167700318597540461), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial(i, T(0.5)), z_t(0.60672961239287904055952, +0.7925599369551407652246), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial(i, o), i, 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial(o, T(0.5)), z_t(0.88622692545275801364908), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial(i, 2*i),    z_t(0.00533756125402432030171473451274, +0.024348078097112309674412896870731), 1.0e-5);
};
