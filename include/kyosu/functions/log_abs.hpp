//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/sqr_abs.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options> struct log_abs_t : eve::elementwise_callable<log_abs_t, Options, eve::pedantic_option>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::real V> KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept { return eve::log_abs(v); }

    KYOSU_CALLABLE_OBJECT(log_abs_t, log_abs_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var log_abs
  //!   @brief Computes the natural logarithm of the absolute value of the argument.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto log_abs(T z) noexcept;
  //!
  //!      // Semantic modifyiers
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto log_abs[pedantic](T z) noexcept;
  //!
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns  `log(abs(z))`.
  //!     Use pedantic if your entries can have absolute values greater than sqrt(valmax).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/log_abs.cpp}
  //======================================================================================================================
  inline constexpr auto log_abs = eve::functor<log_abs_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log_abs_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if (O::contains(eve::pedantic)) return eve::log(kyosu::abs(z));
    else return kyosu::half(kyosu::as<as_real_type_t<Z>>()) * eve::log(kyosu::sqr_abs(z));
  }
}
