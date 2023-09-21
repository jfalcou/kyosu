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
  using z_t = kyosu::complex_t<T>;
 auto tcx = [](auto r,  auto i){return kyosu::to_complex(T(r), T(i)); };
  auto a = tcx(a0, a1);
  auto b = tcx(a2, a3);

  auto rf =  [](auto x,  auto a){return kyosu::tgamma(a+x)/kyosu::tgamma(x); };

  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, b) , rf(a, b),1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, tcx(2, 0)), a*(a+1), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, tcx(3, 0)), a*(a+1)*(a+2),  1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(kyosu::abs(a0), b)   , rf(kyosu::abs(a0), b), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(-kyosu::abs(a0), b)   , rf(-kyosu::abs(a0), b), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(b, kyosu::abs(a0))   ,  rf(b, kyosu::abs(a0)), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, 3u)   , kyosu::rising_factorial(a, e_t(3)),  1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, 2u)   , kyosu::rising_factorial(a, e_t(2)),  1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(a, -2)   , kyosu::rising_factorial(a, e_t(-2)),  1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(tcx(0, 0), tcx(0, 0)), tcx(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(tcx(1, 0), tcx(0, 0)), tcx(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(tcx(1, 3), tcx(0, 0)), tcx(1, 0), 1.0e-5);

  using eve::as;
  auto inf = eve::inf(as<e_t>());
  auto minf = eve::minf(as<e_t>());
  auto nan = eve::nan(as<e_t>());

  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(tcx(inf, 0), tcx(0, 0)), tcx(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(tcx(minf, 0), tcx(0, 0)), tcx(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(tcx(nan, 0), tcx(0, 0)), tcx(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(tcx(nan, 1), tcx(0, 0)), tcx(1, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::rising_factorial(tcx(0, 0),  tcx(0, 0)), tcx(1, 0), 1.0e-5);
  z_t i = tcx(0, 1);
  z_t o = tcx(1, 0);
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial(i, i),      tcx(0.133408195318916183621, +0.06139167700318597540461), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial(i, T(0.5)), tcx(0.60672961239287904055952, +0.7925599369551407652246), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial(i, o), i, 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial(o, T(0.5)), tcx(0.88622692545275801364908, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::rising_factorial(i, 2*i),    tcx(0.00533756125402432030171473451274, +0.024348078097112309674412896870731), 1.0e-5);
};
