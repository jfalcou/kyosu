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

TTS_CASE_WITH ( "Check behavior of lrising_factorial on wide"
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
 auto tcx = [](auto r,  auto i){return kyosu::complex(T(r), T(i)); };
 auto a = tcx(a0, a1);
 auto b = tcx(a2, a3);
 using z_t = kyosu::complex_t<T>;
  z_t i = tcx(T(0), T(1));
  z_t o = tcx(T(1), T(0));
  auto lrf =  [](auto a,  auto b){return kyosu::log(kyosu::tgamma(a+b)/kyosu::tgamma(a)); };
  TTS_RELATIVE_EQUAL( kyosu::lrising_factorial(a, b) , lrf(a, b), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::lrising_factorial(a, 0.0) , tcx(0, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::lrising_factorial(a, 1.0), kyosu::log(a), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::lrising_factorial(a, 2.0), kyosu::log(a*a+a), 1.0e-5);

   using eve::as;
   auto inf = eve::inf(as<e_t>());
   auto minf = eve::minf(as<e_t>());
   auto nan = eve::nan(as<e_t>());

   TTS_RELATIVE_EQUAL( kyosu::lrising_factorial(tcx(inf, 0), tcx(0, 0)), tcx(0, 0), 1.0e-5);
   TTS_RELATIVE_EQUAL( kyosu::lrising_factorial(tcx(minf, 0), tcx(0, 0)), tcx(0, 0), 1.0e-5);
   TTS_RELATIVE_EQUAL( kyosu::lrising_factorial(tcx(nan, 0), tcx(0, 0)), tcx(0, 0), 1.0e-5);
   TTS_RELATIVE_EQUAL( kyosu::lrising_factorial(tcx(nan, 1), tcx(0, 0)), tcx(0, 0), 1.0e-5);
   TTS_RELATIVE_EQUAL( kyosu::lrising_factorial(tcx(0, 0),  tcx(0, 0)), tcx(0, 0), 1.0e-5);
   TTS_RELATIVE_EQUAL(kyosu::lrising_factorial(i, i),  tcx(-1.918302767689018311762010, +0.4312866367773215092712391), 1.0e-5);
   TTS_RELATIVE_EQUAL(kyosu::lrising_factorial(i, T(0.5)), tcx(-0.0018674449025165763, +0.9174289229198607075556282), 1.0e-5);
   TTS_RELATIVE_EQUAL(kyosu::lrising_factorial(o, T(0.5)), tcx(-0.120782237635245222345518445781647212251852727902599468363868473, 0), 1.0e-5);
   TTS_RELATIVE_EQUAL(kyosu::lrising_factorial(i, 2*i),   tcx(-3.69183338895600954408, +1.3549910915361463982113221), 1.0e-5);
};
