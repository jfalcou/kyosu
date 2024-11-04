//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>
#include <eve/module/math.hpp>

namespace kyosu::_
{
  template<typename Func> struct constant_t;

  template<template<typename> typename Func, typename Opts>
  struct constant_t<Func<Opts>> : Func<Opts>
  {
    using base_callable = Func<Opts>;

    template<typename T>
    EVE_FORCEINLINE constexpr auto operator[](T t)
    const requires( requires(base_callable const& b) { b[t];} )
    {
      auto new_traits = base_callable::base::operator[](t);
      return  constant_t<Func<decltype(new_traits)>>{new_traits};
    }

    using base_callable::operator();

    template<concepts::cayley_dickson T>
    requires( requires(base_callable const& b){ b(as<as_real_type_t<T>>{}); } )
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const
    {
      return T{base_callable::operator()(as<as_real_type_t<T>>{})};
    }

    KYOSU_CALLABLE_OBJECT(constant_t, constant_);
  };

  template<auto Constant>
  inline constexpr constant_t<eve::tag_t<Constant>> as_constant = {};
}

//======================================================================================================================
// List of all EVE constants we re-propagate
//======================================================================================================================
namespace kyosu
{
  // Direct reuse
  using eve::zero;
  using eve::true_;
  using eve::false_;

  // Wrapping required
  // from eve::core
  inline constexpr auto allbits                = _::as_constant<eve::allbits>;
  inline constexpr auto bitincrement           = _::as_constant<eve::bitincrement>;
  inline constexpr auto eps                    = _::as_constant<eve::eps>;
  inline constexpr auto half                   = _::as_constant<eve::half>;
  inline constexpr auto inf                    = _::as_constant<eve::inf>;
  inline constexpr auto logeps                 = _::as_constant<eve::logeps>;
  inline constexpr auto maxflint               = _::as_constant<eve::maxflint>;
  inline constexpr auto mhalf                  = _::as_constant<eve::mhalf>;
  inline constexpr auto mindenormal            = _::as_constant<eve::mindenormal>;
  inline constexpr auto minexponent            = _::as_constant<eve::minexponent>;
  inline constexpr auto minf                   = _::as_constant<eve::minf>;
  inline constexpr auto mone                   = _::as_constant<eve::mone>;
  inline constexpr auto mzero                  = _::as_constant<eve::mzero>;
  inline constexpr auto nan                    = _::as_constant<eve::nan>;
  inline constexpr auto one                    = _::as_constant<eve::one>;
  inline constexpr auto oneosqrteps            = _::as_constant<eve::oneosqrteps>;
  inline constexpr auto signmask               = _::as_constant<eve::signmask>;
  inline constexpr auto smallestposval         = _::as_constant<eve::smallestposval>;
  inline constexpr auto sqrteps                = _::as_constant<eve::sqrteps>;
  inline constexpr auto sqrtsmallestposval     = _::as_constant<eve::sqrtsmallestposval>;
  inline constexpr auto sqrtvalmax             = _::as_constant<eve::sqrtvalmax>;
  inline constexpr auto valmax                 = _::as_constant<eve::valmax>;
  inline constexpr auto valmin                 = _::as_constant<eve::valmin>;
  // from eve::math
  inline constexpr auto catalan                = _::as_constant<eve::catalan>;
  inline constexpr auto cbrt_pi                = _::as_constant<eve::cbrt_pi>;
  inline constexpr auto cos_1                  = _::as_constant<eve::cos_1>;
  inline constexpr auto cosh_1                 = _::as_constant<eve::cosh_1>;
  inline constexpr auto egamma                 = _::as_constant<eve::egamma>;
  inline constexpr auto egamma_sqr             = _::as_constant<eve::egamma_sqr>;
  inline constexpr auto epso_2                 = _::as_constant<eve::epso_2>;
  inline constexpr auto euler                  = _::as_constant<eve::euler>;
  inline constexpr auto exp_pi                 = _::as_constant<eve::exp_pi>;
  inline constexpr auto extreme_value_skewness = _::as_constant<eve::extreme_value_skewness>;
  inline constexpr auto four_minus_pi          = _::as_constant<eve::four_minus_pi>;
  inline constexpr auto four_pio_3             = _::as_constant<eve::four_pio_3>;
  inline constexpr auto glaisher               = _::as_constant<eve::glaisher>;
  inline constexpr auto inv_2eps               = _::as_constant<eve::inv_2eps>;
  inline constexpr auto inv_2pi                = _::as_constant<eve::inv_2pi>;
  inline constexpr auto inv_e                  = _::as_constant<eve::inv_e>;
  inline constexpr auto inv_egamma             = _::as_constant<eve::inv_egamma>;
  inline constexpr auto inv_pi                 = _::as_constant<eve::inv_pi>;
  inline constexpr auto invcbrt_pi             = _::as_constant<eve::invcbrt_pi>;
  inline constexpr auto invlog10_2             = _::as_constant<eve::invlog10_2>;
  inline constexpr auto invlog10_e             = _::as_constant<eve::invlog10_e>;
  inline constexpr auto invlog_10              = _::as_constant<eve::invlog_10>;
  inline constexpr auto invlog_2               = _::as_constant<eve::invlog_2>;
  inline constexpr auto invlog_phi             = _::as_constant<eve::invlog_phi>;
  inline constexpr auto invsqrt_2              = _::as_constant<eve::invsqrt_2>;
  inline constexpr auto khinchin               = _::as_constant<eve::khinchin>;
  inline constexpr auto log10_e                = _::as_constant<eve::log10_e>;
  inline constexpr auto log2_e                 = _::as_constant<eve::log2_e>;
  inline constexpr auto log_10                 = _::as_constant<eve::log_10>;
  inline constexpr auto log_2                  = _::as_constant<eve::log_2>;
  inline constexpr auto log_phi                = _::as_constant<eve::log_phi>;
  inline constexpr auto loglog_2               = _::as_constant<eve::loglog_2>;
  inline constexpr auto maxlog                 = _::as_constant<eve::maxlog>;
  inline constexpr auto maxlog10               = _::as_constant<eve::maxlog10>;
  inline constexpr auto maxlog2                = _::as_constant<eve::maxlog2>;
  inline constexpr auto minlog                 = _::as_constant<eve::minlog>;
  inline constexpr auto minlog10               = _::as_constant<eve::minlog10>;
  inline constexpr auto minlog10denormal       = _::as_constant<eve::minlog10denormal>;
  inline constexpr auto minlog2                = _::as_constant<eve::minlog2>;
  inline constexpr auto minlog2denormal        = _::as_constant<eve::minlog2denormal>;
  inline constexpr auto minlogdenormal         = _::as_constant<eve::minlogdenormal>;
//  inline constexpr auto oneotwoeps             = _::as_constant<eve::oneotwoeps>; //include forgotten in eve TO BE FIXED
  inline constexpr auto phi                    = _::as_constant<eve::phi>;
  inline constexpr auto pi                     = _::as_constant<eve::pi>;
  inline constexpr auto pi2                    = _::as_constant<eve::pi2>;
  inline constexpr auto pi2o_16                = _::as_constant<eve::pi2o_16>;
  inline constexpr auto pi2o_6                 = _::as_constant<eve::pi2o_6>;
  inline constexpr auto pi3                    = _::as_constant<eve::pi3>;
  inline constexpr auto pi_minus_3             = _::as_constant<eve::pi_minus_3>;
  inline constexpr auto pi_pow_e               = _::as_constant<eve::pi_pow_e>;
  inline constexpr auto pio_2                  = _::as_constant<eve::pio_2>;
  inline constexpr auto pio_3                  = _::as_constant<eve::pio_3>;
  inline constexpr auto pio_4                  = _::as_constant<eve::pio_4>;
  inline constexpr auto pio_6                  = _::as_constant<eve::pio_6>;
  inline constexpr auto quarter                = _::as_constant<eve::quarter>;
  inline constexpr auto rayleigh_kurtosis      = _::as_constant<eve::rayleigh_kurtosis>;
  inline constexpr auto rayleigh_kurtosis_excess = _::as_constant<eve::rayleigh_kurtosis_excess>;
  inline constexpr auto rayleigh_skewness      = _::as_constant<eve::rayleigh_skewness>;
  inline constexpr auto rsqrt_2pi              = _::as_constant<eve::rsqrt_2pi>;
  inline constexpr auto rsqrt_e                = _::as_constant<eve::rsqrt_e>;
  inline constexpr auto rsqrt_pi               = _::as_constant<eve::rsqrt_pi>;
  inline constexpr auto rsqrt_pio_2            = _::as_constant<eve::rsqrt_pio_2>;
  inline constexpr auto sin_1                  = _::as_constant<eve::sin_1>;
  inline constexpr auto sinh_1                 = _::as_constant<eve::sinh_1>;
  inline constexpr auto sixth                  = _::as_constant<eve::sixth>;
  inline constexpr auto sqrt_2                 = _::as_constant<eve::sqrt_2>;
  inline constexpr auto sqrt_2pi               = _::as_constant<eve::sqrt_2pi>;
  inline constexpr auto sqrt_3                 = _::as_constant<eve::sqrt_3>;
  inline constexpr auto sqrt_e                 = _::as_constant<eve::sqrt_e>;
  inline constexpr auto sqrt_pi                = _::as_constant<eve::sqrt_pi>;
  inline constexpr auto sqrt_pio_2             = _::as_constant<eve::sqrt_pio_2>;
  inline constexpr auto sqrtlog_4              = _::as_constant<eve::sqrtlog_4>;
  inline constexpr auto third                  = _::as_constant<eve::third>;
  inline constexpr auto three_o_4              = _::as_constant<eve::three_o_4>;
  inline constexpr auto three_pio_4            = _::as_constant<eve::three_pio_4>;
  inline constexpr auto two_o_3                = _::as_constant<eve::two_o_3>;
  inline constexpr auto two_o_pi               = _::as_constant<eve::two_o_pi>;
  inline constexpr auto two_o_sqrt_pi          = _::as_constant<eve::two_o_sqrt_pi>;
  inline constexpr auto two_pi                 = _::as_constant<eve::two_pi>;
  inline constexpr auto two_pio_3              = _::as_constant<eve::two_pio_3>;
  inline constexpr auto zeta_2                 = _::as_constant<eve::zeta_2>;
  inline constexpr auto zeta_3                 = _::as_constant<eve::zeta_3>;

}
