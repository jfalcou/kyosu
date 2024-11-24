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
#include <kyosu/functions/deta.hpp>

namespace kyosu
{
  template<typename Options>
  struct eta_t : eve::elementwise_callable<eta_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return deta(1u, z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return (*this)(complex(v)); }

    KYOSU_CALLABLE_OBJECT(eta_t, eta_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var eta
//!   @brief Computes the Dirichlet sum \f$ \displaystyle \sum_0^\infty \frac{(-1)^n}{(n+1)^z}\f$.
//!   Sometimes this function is for obvious reasons called the alternative \f$\zeta\f$ function .
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
//!      template<unsigned_scalar_value K, eve::ordered_value T>              constexpr auto eta(T z) noexcept;  //1
//!      template<unsigned_scalar_value K, kyosu::concepts::cayley_dickson T> constexpr auto eta(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : value to process.
//!
//! **Return value**
//!
//!   Returns the Dirichlet alternating zeta function: \f$  \displaystyle \sum_0^\infty \frac{(-1)^n}{(n+1)^z}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/eta.cpp}
//======================================================================================================================
  inline constexpr auto eta = eve::functor<eta_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
