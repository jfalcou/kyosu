//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>


TTS_CASE_TPL( "test constants", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using kyosu::octonion_t;

#define TEST_CTS(cts)                                                            \
{                                                                                \
  T v(eve::cts(eve::as<T>{}));                                                   \
  TTS_IEEE_EQUAL(kyosu::cts(kyosu::as<T>{})               , v                 ); \
  TTS_IEEE_EQUAL(kyosu::cts(kyosu::as<complex_t<T>>{})    , complex_t<T>{v}   ); \
  TTS_IEEE_EQUAL(kyosu::cts(kyosu::as<quaternion_t<T>>{}) , quaternion_t<T>{v}); \
  TTS_IEEE_EQUAL(kyosu::cts(kyosu::as<octonion_t<T>>{})   , octonion_t<T>{v}  ); \
}                                                                                \
/**/

  TEST_CTS(allbits);
  TEST_CTS(bitincrement);
  TEST_CTS(eps);
  TEST_CTS(half);
  TEST_CTS(inf);
  TEST_CTS(logeps);
  TEST_CTS(maxflint);
  TEST_CTS(mhalf);
  TEST_CTS(mindenormal);
  TEST_CTS(minf);
  TEST_CTS(mone);
  TEST_CTS(mzero);
  TEST_CTS(nan);
  TEST_CTS(one);
  TEST_CTS(oneosqrteps);
  TEST_CTS(signmask);
  TEST_CTS(smallestposval);
  TEST_CTS(sqrteps);
  TEST_CTS(sqrtsmallestposval);
  TEST_CTS(sqrtvalmax);
  TEST_CTS(valmax);
  TEST_CTS(valmin);

  TEST_CTS(catalan);
  TEST_CTS(cbrt_pi);
  TEST_CTS(cos_1);
  TEST_CTS(cosh_1);
  TEST_CTS(egamma);
  TEST_CTS(egamma_sqr);
  TEST_CTS(epso_2);
  TEST_CTS(euler);
  TEST_CTS(exp_pi);
  TEST_CTS(extreme_value_skewness);
  TEST_CTS(four_minus_pi);
  TEST_CTS(four_pio_3);
  TEST_CTS(glaisher);
  TEST_CTS(inv_2eps);
  TEST_CTS(inv_2pi);
  TEST_CTS(inv_e);
  TEST_CTS(inv_egamma);
  TEST_CTS(inv_pi);
  TEST_CTS(invcbrt_pi);
  TEST_CTS(invlog10_2);
  TEST_CTS(invlog10_e);
  TEST_CTS(invlog_10);
  TEST_CTS(invlog_2);
  TEST_CTS(invlog_phi);
  TEST_CTS(invsqrt_2);
  TEST_CTS(khinchin);
  TEST_CTS(log10_e);
  TEST_CTS(log2_e);
  TEST_CTS(log_10);
  TEST_CTS(log_2);
  TEST_CTS(log_phi);
  TEST_CTS(loglog_2);
  TEST_CTS(maxlog);
  TEST_CTS(maxlog10);
  TEST_CTS(maxlog2);
  TEST_CTS(minlog);
  TEST_CTS(minlog10);
  TEST_CTS(minlog10denormal);
  TEST_CTS(minlog2);
  TEST_CTS(minlog2denormal);
  TEST_CTS(minlogdenormal);
  TEST_CTS(phi);
  TEST_CTS(pi);
  TEST_CTS(pi2);
  TEST_CTS(pi2o_16);
  TEST_CTS(pi2o_6);
  TEST_CTS(pi3);
  TEST_CTS(pi_minus_3);
  TEST_CTS(pi_pow_e);
  TEST_CTS(pio_2);
  TEST_CTS(pio_3);
  TEST_CTS(pio_4);
  TEST_CTS(pio_6);
  TEST_CTS(quarter);
  TEST_CTS(rayleigh_kurtosis);
  TEST_CTS(rayleigh_kurtosis_excess);
  TEST_CTS(rayleigh_skewness);
  TEST_CTS(rsqrt_2pi);
  TEST_CTS(rsqrt_e);
  TEST_CTS(rsqrt_pi);
  TEST_CTS(rsqrt_pio_2);
  TEST_CTS(sin_1);
  TEST_CTS(sinh_1);
  TEST_CTS(sixth);
  TEST_CTS(sqrt_2);
  TEST_CTS(sqrt_2pi);
  TEST_CTS(sqrt_3);
  TEST_CTS(sqrt_e);
  TEST_CTS(sqrt_pi);
  TEST_CTS(sqrt_pio_2);
  TEST_CTS(sqrtlog_4);
  TEST_CTS(third);
  TEST_CTS(three_o_4);
  TEST_CTS(three_pio_4);
  TEST_CTS(two_o_3);
  TEST_CTS(two_o_pi);
  TEST_CTS(two_o_sqrt_pi);
  TEST_CTS(two_pi);
  TEST_CTS(two_pio_3);
  TEST_CTS(zeta_2);
  TEST_CTS(zeta_3);
};
