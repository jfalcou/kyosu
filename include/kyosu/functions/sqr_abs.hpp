//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct sqr_abs_t : eve::elementwise_callable<sqr_abs_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept { return KYOSU_CALL(v); }

    KYOSU_CALLABLE_OBJECT(sqr_abs_t, sqr_abs_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sqr_abs
//!   @brief Computes the squared sqr_absolute value of the parameter.
//!
//!   **Defined in Header**
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr as_real_type_t<T>  sqr_abs(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto               sqr_abs(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the squared modulus of its argument, a floating value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sqr_abs.cpp}
//======================================================================================================================
  inline constexpr auto sqr_abs = eve::functor<sqr_abs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sqr_abs_(KYOSU_DELAY(), O const&, Z const& v) noexcept
  {
    if constexpr(concepts::cayley_dickson<Z>)
    {
      auto anyinf = kumi::any_of(v, eve::is_infinite);
      auto squares = kumi::map([](auto const& e) { return e*e; }, v);
      auto r = kumi::sum( kumi::extract(squares,kumi::index<1>), get<0>(squares));
      return if_else(anyinf,  eve::inf(as(r)), r);
    }
    else return eve::sqr(v);
  }
}
