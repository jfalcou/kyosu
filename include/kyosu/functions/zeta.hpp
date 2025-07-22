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
#include <kyosu/functions/eta.hpp>
#include <kyosu/functions/if_else.hpp>

namespace kyosu
{
  template<typename Options>
  struct zeta_t : eve::elementwise_callable<zeta_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(complex(z));
      else if constexpr(concepts::complex<Z> )
        return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(zeta_t, zeta_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var zeta
//!   @brief Computes the Riemann \f$ \displaystyle\zeta(z)=\sum_0^\infty \frac{1}{(n+1)^z}\f$.
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
//!      template<kyosu::concepts::complex T>    constexpr auto zeta(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : value to process.
//!
//! **Return value**
//!
//!   Returns the Dirichlet zeta sum: \f$  \displaystyle \sum_0^\infty \frac{1}{(n+1)^z}\f$
//!
//!  @note ζ can be used as an alias in code.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Dirichlet series](https://en.wikipedia.org/wiki/Dirichlet_series)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/zeta.cpp}
//======================================================================================================================
  inline constexpr auto zeta = eve::functor<zeta_t>;
  inline constexpr auto ζ = eve::functor<zeta_t>;

//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto zeta_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
   if constexpr(concepts::complex<Z> )
    {
      auto zz=exp2(z);
      auto k = zz/(zz-2);
      auto g = if_else(z == Z(1), complex(eve::nan(eve::as(real(z)))), k*eta(z));
      return if_else(real(z) == eve::inf(eve::as(real(z))), complex(eve::one(eve::as(real(z)))), g);
    }
    else
    {
      return cayley_extend(kyosu::zeta, z);
    }
  }
}
