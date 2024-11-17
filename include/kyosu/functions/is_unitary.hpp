//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct is_unitary_t : eve::elementwise_callable<is_unitary_t, Options, eve::raw_option, eve::pedantic_option>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::abs(v) == eve::one(eve::as(v)); }

    KYOSU_CALLABLE_OBJECT(is_unitary_t, is_unitary_);
  };


//!   {
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_unitary
//!   @brief test if the parameter is unitary (absolute value one).
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
//!      Regular call
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_unitary(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_unitary(T z) noexcept;
//!
//!      Semantic modifyier
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_unitary[pedantic](T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_unitary[pedantic](T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. Returns elementwise true if the element is of absolute value one (with some ulps laxism).
//!     2. Insists on the norm being strictly equal to one.
//!
//!  @note normalization of cayley-dickson values is rarely perfect, so by default `is_unitary` tolerate
//!     that the computed norm is `almost` equal to one. The rationale is that if one normalize a cayley-dickson
//!     (using for example the `sign` function) he probably intends that `is_unitary`
//!     has to return true on the result of the normalization.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_unitary.cpp}
//======================================================================================================================
  inline constexpr auto is_unitary = eve::functor<is_unitary_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto is_unitary_(KYOSU_DELAY(), O const&, Z c) noexcept
  {
    using ar_t = decltype(kyosu::sqr_abs(c));
    if constexpr(O::contains(eve::pedantic))
    {
      return kyosu::sqr_abs(c) == eve::one(eve::as<ar_t>());
    }
    else
    {
      // almost is used to encompass the fact that normalization of cayley_dickson can suffer
      // rounding errors. Whhen available use raw if you don't accept this behavior.
      return eve::is_equal[eve::almost](kyosu::sqr_abs(c), eve::one(eve::as<ar_t>()));
    }
  }
}
