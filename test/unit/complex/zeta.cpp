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


TTS_CASE_WITH("Check behavior of zeta on wide"
             , kyosu::scalar_real_types
             , tts::generate( tts::randoms(-10, 10))
             )
  <typename T>([[maybe_unused]] T const& a0)
{
  using eve::as;
  using kyosu::real;
  using kyosu::zeta;
  using v_t = eve::element_type_t<T>;

#if defined(__cpp_lib_math_special_functions)
//  TTS_RELATIVE_EQUAL(real(zeta(a0)), map([](auto e) -> v_t { return std::riemann_zeta(v_t(e)); }, a0), 01.0e-4);
  TTS_ULP_EQUAL(real(zeta(T(0))), T(std::riemann_zeta(v_t(0))), 0.5);
  TTS_ULP_EQUAL(real(zeta(T(-0.0))), T(std::riemann_zeta(v_t(-0.0))), 0.5);
  TTS_ULP_EQUAL(real(zeta(T(1.5))), T(std::riemann_zeta(v_t(1.5))), 2.5);
  TTS_ULP_EQUAL(real(zeta(T(-1.5))), T(std::riemann_zeta(v_t(-1.5))), 3.5);
  TTS_ULP_EQUAL(real(zeta(T(14))), T(std::riemann_zeta(v_t(14))), 0.5);
  TTS_ULP_EQUAL(real(zeta(T(-14))), T(std::riemann_zeta(v_t(-14))), 0.5);
  TTS_ULP_EQUAL(real(zeta(T(14.5))), T(std::riemann_zeta(v_t(14.5))), 0.5);
  TTS_ULP_EQUAL(real(zeta(T(-14.5))), T(std::riemann_zeta(v_t(-14.5))), 18);
#endif

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(real(zeta(eve::nan(eve::as<T>()))), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(real(zeta(eve::inf(eve::as<T>()))), eve::one(eve::as<T>()));
    TTS_IEEE_EQUAL(real(zeta(eve::minf(eve::as<T>()))), eve::nan(eve::as<T>()));
  };

  TTS_IEEE_EQUAL(real(zeta(T(1))), eve::nan(eve::as<T>()));
};
