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
#include <kyosu/functions/is_not_nan.hpp>


namespace kyosu
{
  template<typename Options>
  struct is_not_equal_t : eve::strict_elementwise_callable<is_not_equal_t, Options, eve::numeric_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    KYOSU_FORCEINLINE constexpr eve::common_logical_t<as_real_type_t<Z0>,as_real_type_t<Z1>>
    operator()(Z0 const& z0, Z1 const & z1) const noexcept
    {
       return KYOSU_CALL(z0, z1);
    }

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
//!     2. NaN values in correspoding parts are considered equal
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

namespace kyosu::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto is_not_equal_(KYOSU_DELAY(), O const& opts, Z0 z0,  Z1 z1) noexcept
  {
    if constexpr(O::contains(eve::numeric))
    {
      if constexpr(concepts::real<Z0> && concepts::real<Z1>) return eve::is_not_equal[eve::numeric](z0, z1);
      else
      {
        return kumi::map([](auto a,  auto b) { return eve::is_not_equal[eve::numeric](a, b); }, r_t(z0), r_t(z1));
      }
    }
    else return z0 != z1;
  }
}
