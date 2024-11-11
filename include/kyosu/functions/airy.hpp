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
  struct airy_t : eve::elementwise_callable<airy_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr kumi::tuple<Z, Z>operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr kumi::tuple<V, V> operator()(V v) const noexcept
    { return eve::airy(v); }

    KYOSU_CALLABLE_OBJECT(airy_t, airy_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var airy
//!   @brief Computes simultaneously the airy functions \f$Ai\f$ and \f$Bi\f$.
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
//!      template<eve::floating_ordered_value T> constexpr auto airy(T z) noexcept;
//!
//!      template<kyosu::concepts::cayley_dickson T>  constexpr auto airy(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  a kumi pair containing \f$\{Ai(z)\}f$ and \f$\{Bi(z)\}f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/airy.cpp}
//======================================================================================================================
  inline constexpr auto airy = eve::functor<airy_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto airy_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto [sqzo3, zeta] = zet(z);
    auto ip = cyl_bessel_i(eve::third(as<u_t>()), zeta);
    auto im = cyl_bessel_i(-eve::third(as<u_t>()), zeta);
    return kumi::tuple{ invpi(as<u_t>())*sqzo3*(im-ip),  sqzo3*(ip+im)};
  }
}
