//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/is_nan.hpp>

namespace kyosu
{
  template<typename Options>
  struct is_equal_t : eve::strict_elementwise_callable<is_equal_t, Options, eve::numeric_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept -> decltype(z0 == z1)
    {
      if constexpr(Options::contains(eve::numeric))
        return kumi::map([](auto a,  auto b) { return eve::is_equal[eve::numeric](a, b); }, r_t(z0), r_t(z1));
      else
        return z0 == z1;
    }

    KYOSU_CALLABLE_OBJECT(is_equal_t, is_equal_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_equal
//!   @brief retuen true if and only if the two parameters are equal.
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
//!      constexpr auto is_equal(auto z0, auto z1)          noexcept; //1
//!
//!      Semantic modifyier
//!      constexpr auto is_equal[numeric](auto z0, auto z1) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!     1. Returns elementwise true or false according the equality of the parameters
//!     2. NaN values in correspoding parts are considered equal
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_equal.cpp}
//======================================================================================================================
  inline constexpr auto is_equal = eve::functor<is_equal_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
