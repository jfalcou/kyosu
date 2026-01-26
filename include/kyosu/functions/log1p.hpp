//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/inc.hpp>
#include <kyosu/functions/arg.hpp>

namespace kyosu
{
  template<typename Options>
  struct log1p_t : eve::strict_elementwise_callable<log1p_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like  Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<kyosu::complexify_if_t<Options, Z>, K>
    operator()(Z const& z, K const & k) const noexcept
    requires(eve::same_lanes_or_scalar<Z, K>)
    {
      return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(log1p_t, log1p_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log1p
//!   @brief Computes the natural logarithm of the argument plus 1.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!      //  regular call
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log1p(T z) noexcept;
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log1p(T z eve::value n) noexcept;
//!
//!      // semantic modifyers
//!      template<concepts::real T> constexpr complexify_t<T> log1p[real_only](T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     - A real typed input z is treated as if `complex(z)` was entered, unless the option real_only is used
//!       in which case the parameter must be a floating_value, the real part of the result will the same as an eve::log1p
//!       implying a Nan result if the result is not real.
//!     - For real and complex entries provisions are made to get better precision near z = 0.
//!     - Returns [log](@ref kyosu::log)(1+z).
//!     - with two parameters return the nth branch of the logarithm of `1+z`.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/log1p.cpp}
//======================================================================================================================
  inline constexpr auto log1p = eve::functor<log1p_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  constexpr auto log1p_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr(O::contains(real_only) && concepts::real<Z>)
      return eve::log1p[o.drop(real_only)](z);
    else if constexpr(concepts::real<Z> )
      return kyosu::log1p[o](complex(z));
    else if constexpr(kyosu::concepts::complex<Z>)
    {
      auto m = kyosu::inc(z);
      auto theta = eve::if_else((kyosu::is_real(m) && eve::is_nltz(kyosu::real(m))), eve::zero, kyosu::arg(m)) ;
      auto rz =  kyosu::real(z);
      auto iz2 =  eve::sqr(kyosu::imag(z));
      auto r = eve::half(eve::as(theta))*eve::log1p(rz*(rz+2)+iz2);
      return complex(r, theta);
    }
    else
    {
      return _::cayley_extend(kyosu::log1p, z);
    }
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log1p_(KYOSU_DELAY(), O const&o, Z z, K k) noexcept
  requires(!O::contains(real_only))
  {
    if constexpr(kyosu::concepts::real<Z>)
      return log1p[o](complex(z));
    else if constexpr(kyosu::concepts::complex<Z>)
    {
      using e_t = eve::element_type_t<decltype(real(z))>;
      auto kk = eve::convert(k, as<e_t>());
      return  log1p[o](z)+muli(kk*two_pi(as(kk)));
    }
    else
    {
      return _::cayley_extend(kyosu::log1p, z, k);
    }
  }

  template<concepts::real Z, eve::value ...K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log1p_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), log1p(z, k...));
  }

}
