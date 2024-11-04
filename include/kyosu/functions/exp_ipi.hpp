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
#include <kyosu/functions/muli.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct exp_ipi_t : eve::elementwise_callable<exp_ipi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return  KYOSU_CALL(v); }

    KYOSU_CALLABLE_OBJECT(exp_ipi_t, exp_ipi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp_ipi
//!   @brief Computes the exponential of \f$i\pi\f$ times the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexp_ipir T exp_ipi(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexp_ipir T exp_ipi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns  `exp(i*pi(as(z))*z)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp_ipi.cpp}
//======================================================================================================================
  inline constexpr auto exp_ipi = eve::functor<exp_ipi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto exp_ipi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto [rz, iz] = muli(z);
      auto [s, c]   = eve::sinpicospi(iz);
      auto rho = eve::exp(rz*eve::pi(eve::as(rz)));
      return eve::if_else(kyosu::is_real(z) || rz == eve::minf(eve::as(rz)),
                          kyosu::complex(rho, eve::zero(eve::as(rho))),
                          kyosu::complex(rho*c, rho*s)
                         );
    }
    else
    {
      const auto ipi = muli(pi(eve::as_element<Z>()));
      return kyosu::exp(ipi*z);
    }
  }
}
