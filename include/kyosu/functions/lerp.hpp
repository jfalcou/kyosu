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

namespace kyosu
{
  template<typename Options>
  struct lerp_t : eve::strict_elementwise_callable<lerp_t, Options>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, concepts::real Z2>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& c0, Z1 const & c1, Z2 const & t) const noexcept -> decltype(c0+c1+t)
    {
      return KYOSU_CALL(c0, c1, t);
    }

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
//!  @groupheader{External references}
//!   *  [Wikipedia: Linear interpolation](https://en.wikipedia.org/wiki/Linear_interpolation)
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
  template<typename Z0, typename Z1, typename Z2, eve::callable_options O>
  constexpr KYOSU_FORCEINLINE auto lerp_(KYOSU_DELAY(), O const&, Z0 const& c0, Z1 const& c1, Z2 const& t)
  {
    if constexpr(concepts::real<Z0> && concepts::real<Z1>)
      return eve::lerp(c0,c1,t);
    else
    {
      using r_t = as_cayley_dickson_t<Z0,Z1,Z2>;
      return r_t{kumi::map([&t](auto const& e, auto const & f) { return eve::lerp(e, f, t); }, r_t(c0), r_t(c1))};
    }
  }
}
