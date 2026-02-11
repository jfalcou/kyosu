//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/muli.hpp>

namespace kyosu
{
  template<typename Options> struct log10_t : eve::strict_elementwise_callable<log10_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<kyosu::complexify_if_t<Options, Z>, K> operator()(
      Z const& z, K const& k) const noexcept
    requires(eve::same_lanes_or_scalar<Z, K>)
    {
      return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(log10_t, log10_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var log10
  //!   @brief Computes the base 10 logarithm of the argument.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log10(T z) noexcept;             \\1
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log10(T z eve::value n) noexcept;\\2
  //!
  //!      // semantic modifyers
  //!      template<concepts::real T> constexpr T log10[real_only](T z) noexcept;                                      \\1
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!   1.  a real typed input `z` is treated as if `complex(z)` was entered, unless the option real_only is used
  //!       in which case the parameter must be a floating_value,  the  result will the same as to an `eve::log10` call
  //!       implying a Nan result if the  input is not greater than zero.
  //!   2.  returns [log](@ref kyosu::log)(z)/log_10(as(z)).
  //!   3.  with two parameters return the nth branch of the function.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Common Logarithm](https://mathworld.wolfram.com/CommonLogarithm.html)
  //!   *  [Wikipedia: Logarithm](https://en.wikipedia.org/wiki/Logarithm)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/log10.cpp}
  //======================================================================================================================
  inline constexpr auto log10 = eve::functor<log10_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<concepts::cayley_dickson_like Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log10_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr (O::contains(real_only) && concepts::real<Z>) return eve::log10[o.drop(real_only)](z);
    else if constexpr (concepts::real<Z>) return kyosu::log10[o](complex(z));
    else if constexpr (kyosu::concepts::complex<Z>) { return log(z) * eve::invlog_10(eve::as(real(z))); }
    else return _::cayley_extend(kyosu::log10, z);
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log10_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  requires(!O::contains(real_only))
  {
    if constexpr (kyosu::concepts::real<Z>) return log10[o](complex(z), k);
    else if constexpr (kyosu::concepts::complex<Z>)
    {
      using e_t = eve::element_type_t<decltype(real(z))>;
      auto kk = eve::convert(k, as<e_t>());
      return log(z) * eve::invlog_10(eve::as(real(z))) + kyosu::muli(kk * eve::invlog_10(eve::as(kk)));
      ;
    }
    else return _::cayley_extend(kyosu::log10, z, k);
  }

  template<concepts::real Z, eve::value... K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log10_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), log10(z, k...));
  }
}
