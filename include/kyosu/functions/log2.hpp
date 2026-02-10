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
  template<typename Options> struct log2_t : eve::strict_elementwise_callable<log2_t, Options, real_only_option>
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

    KYOSU_CALLABLE_OBJECT(log2_t, log2_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var log2
  //!   @brief Computes the principal branch of the base 2 logarithm of the argument.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log2(T z)              noexcept; //1
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log2(T z eve::value k) noexcept; //2
  //!
  //!      // semantic modifyers
  //!      template<concepts::real T> constexpr T log2[real_only](T z)                                       noexcept; //1
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
  //!       in which case the parameter must be a floating_value,  the  result will the same as to an `eve::log2` call
  //!       implying a Nan result if the  input is not greater than zero.
  //!   2.  returns [log](@ref kyosu::log)(z)/log_2(as(z)).
  //!   3.  with two parameters return the nth branch of the function.
  //!
  //!  @groupheader{External references}
  //!   *  [Wikipedia: Binary Logarithm](https://en.wikipedia.org/wiki/Binary_logarithm)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/log2.cpp}
  //======================================================================================================================
  inline constexpr auto log2 = eve::functor<log2_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<concepts::cayley_dickson_like Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log2_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr (O::contains(real_only) && concepts::real<Z>) return eve::log2[o.drop(real_only)](z);
    else if constexpr (concepts::real<Z>) return kyosu::log2[o](complex(z));
    else if constexpr (kyosu::concepts::complex<Z>) { return log(z) * eve::invlog_2(eve::as(real(z))); }
    else return _::cayley_extend(kyosu::log2, z);
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log2_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  requires(!O::contains(real_only))
  {
    if constexpr (kyosu::concepts::real<Z>) return log2[o](complex(z), k);
    else if constexpr (kyosu::concepts::complex<Z>)
    {
      using e_t = eve::element_type_t<decltype(real(z))>;
      auto kk = eve::convert(k, as<e_t>());
      return log(z) * eve::invlog_2(eve::as(real(z))) + kyosu::muli(kk * eve::invlog_2(eve::as(kk)));
      ;
    }
    else return _::cayley_extend(kyosu::log2, z, k);
  }

  template<concepts::real Z, eve::value... K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log2_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), log2(z, k...));
  }
}
