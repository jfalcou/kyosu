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
#include <kyosu/functions/argpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct to_polarpi_t : eve::elementwise_callable<to_polarpi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr  kumi::tuple<as_real_type_t<Z>, as_real_type_t<Z>, Z>
    operator()(Z const& z) const noexcept
    requires (dimension_v<Z> > 2)
    { return KYOSU_CALL(z); }

    template<concepts::complex Z>
    KYOSU_FORCEINLINE constexpr  kumi::tuple<as_real_type_t<Z>, as_real_type_t<Z>>
    operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr kumi::tuple<V, V>
    operator()(V v) const noexcept
    { return (*this)(complex(v)); }

    KYOSU_CALLABLE_OBJECT(to_polarpi_t, to_polarpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var to_polarpi
//!   @brief  returns modulus and argument (in \f$\pi\f$ multiples) of the input.
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
//!      template<kyosu::concepts::complex T> constexpr T to_polarpi(T z) noexcept;
//!      template<eve::floating_value T>      constexpr T to_polarpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to put in polar coordinates.
//!
//!   **Return value**
//!
//!     Returns  The kumi tuple `{rho, theta}`. for real and complex with theta in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/to_polarpi.cpp}
//======================================================================================================================
  inline constexpr auto to_polarpi = eve::functor<to_polarpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto to_polarpi_(KYOSU_DELAY(), O const&, C c) noexcept
  {
    if constexpr(kyosu::concepts::complex<C>)
      return kumi::tuple{kyosu::abs(c),  kyosu::argpi(c)};
    else
      return kumi::tuple{kyosu::abs(c),  kyosu::argpi(c), sign(ipart(c))*sign(pure(c))};
  }
}
