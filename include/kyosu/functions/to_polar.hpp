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
#include <kyosu/functions/pure.hpp>

namespace kyosu
{
  template<typename Options>
  struct to_polar_t : eve::elementwise_callable<to_polar_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr  kumi::tuple<as_real_type_t<Z>, as_real_type_t<Z>, Z>
    operator()(Z const& z) const noexcept
    requires(dimension_v<Z> > 2)
    { return KYOSU_CALL(z); }

    template<concepts::complex Z>
    KYOSU_FORCEINLINE constexpr  kumi::tuple<as_real_type_t<Z>, as_real_type_t<Z>>
    operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr kumi::tuple<V, V>
    operator()(V v) const noexcept
    { return (*this)(complex(v)); }

    KYOSU_CALLABLE_OBJECT(to_polar_t, to_polar_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var to_polar
//!   @brief returns modulus and argument of the input.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T to_polar(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T to_polar(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to put in polar coordinates.
//!
//!   **Return value**
//!
//!     Returns  The kumi tuple `{rho, theta}`. for real and commplex and `{rho, theta, I}` for other cayley-dickson
//!     where \f$\textrm{I}\f$ is pure and \f$\textrm{I}^2 = -1 \f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/to_polar.cpp}
//======================================================================================================================
  inline constexpr auto to_polar = eve::functor<to_polar_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto to_polar_(KYOSU_DELAY(), O const&, C c) noexcept
  {
    if constexpr(kyosu::concepts::complex<C>)
      return kumi::tuple{kyosu::abs(c),  kyosu::arg(c)};
    else
      return kumi::tuple{kyosu::abs(c),  kyosu::arg(c), sign(ipart(c))*sign(pure(c))};
  }
}
