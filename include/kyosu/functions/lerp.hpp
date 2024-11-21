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

namespace kyosu
{
  template<typename Options>
  struct lerp_t : eve::strict_elementwise_callable<lerp_t, Options>
  {
    template<typename Z0, typename Z1, typename Z2>
    requires((concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)&& concepts::real<Z2>)
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& z0, Z1 const & z1, Z2 const & z2) const noexcept -> decltype(z0+z1+z2)
    { return KYOSU_CALL(z0,z1,z2); }

    template<concepts::real V0, concepts::real V1, concepts::real V2>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1, V2 v2) const noexcept -> decltype(v0+v1+v2)
    { return eve::lerp(v0,v1,v2); }

    KYOSU_CALLABLE_OBJECT(lerp_t, lerp_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lerp
//!   @brief  Computes the  linear interpolation.
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
//!     constexpr auto lerp(auto z0, auto z1, floating_ordered_value t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!     * `t`: floating value interpolation coefficient.
//!
//!   **Return value**
//!
//!    The value of the interpolation (or extrapolation)  between `z0` and `z1` is returned.
//!    The call is semantically equivalent to `z0+t*(z1-z0)`.
//!
//!    @see slerp for better unitary quaternion (spheroidal) interpolation.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lerp.cpp}
//======================================================================================================================
  inline constexpr auto lerp = eve::functor<lerp_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename C0, typename C1, typename T, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto lerp_(KYOSU_DELAY(), O const&, C0 c0, C1 c1, T t) noexcept
  {
    using r_t = as_cayley_dickson_t<C0,C1,T>;
    return r_t{kumi::map([&t](auto const& e, auto const & f) { return eve::lerp(e, f, t); }, r_t(c0), r_t(c1))};
  }
}
