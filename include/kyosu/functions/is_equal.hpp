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
    KYOSU_FORCEINLINE constexpr eve::common_logical_t<as_real_type_t<Z0>,as_real_type_t<Z1>>
    operator()(Z0 const& z0, Z1 const & z1) const noexcept
    {
       return KYOSU_CALL(z0, z1);
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

namespace kyosu::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto is_equal_(KYOSU_DELAY(), O const& opts, Z0 z0,  Z1 z1) noexcept
  {
    if constexpr(O::contains(eve::numeric))
    {
      if constexpr(concepts::real<Z0> && concepts::real<Z1>) return eve::is_equal[eve::numeric](z0, z1);
      else
      {
        using c_t = decltype(z0 + z1);
        return kumi::all_of(kumi::map([](auto a,  auto b) { return eve::is_equal[eve::numeric](a, b); }, z0, z1));
      }
    }
    else return z0 == z1;
  }
}
