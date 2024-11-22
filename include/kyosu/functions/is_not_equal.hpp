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
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/is_not_nan.hpp>


namespace kyosu
{
  template<typename Options>
  struct is_not_equal_t : eve::strict_elementwise_callable<is_not_equal_t, Options, eve::numeric_option>
  {
    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept -> eve::as_logical_t<decltype(z0 + z1)>
    {
      if constexpr(Options::contains(eve::numeric))
        return (z0 != z1) || (is_not_nan(z0) && is_not_nan(z1));
      else
        return z0 != z1;
    }

    template<concepts::real V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept ->  eve::as_logical_t<decltype(v0 + v1)>
    { return eve::is_not_equal[this->options()](v0, v1); }

    KYOSU_CALLABLE_OBJECT(is_not_equal_t, is_not_equal_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_not_equal
//!   @brief return true if and only if the two parameters are not equal.
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
//!      constexpr auto is_not_equal(auto z0, auto z1)          noexcept; //1
//!
//!      Semantic modifyier
//!      constexpr auto is_not_equal[numeric](auto z0, auto z1) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!     1. Returns elementwise false or true according the equality of the parameters
//!     2. NaN values are considered equal
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_not_equal.cpp}
//======================================================================================================================
  inline constexpr auto is_not_equal = eve::functor<is_not_equal_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
