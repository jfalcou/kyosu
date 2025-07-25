//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/dec.hpp>
#include <kyosu/functions/zeta.hpp>
#include <kyosu/functions/if_else.hpp>

namespace kyosu
{
  template<typename Options>
  struct xi_t : eve::elementwise_callable<xi_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(complex(z));
      else if constexpr(concepts::complex<Z> )
        return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(xi_t, xi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var xi
//!   @brief Computes the Riemann \f$ \displaystyle\xi(z)=\sum_0^\infty \frac{1}{(n+1)^z}\f$.
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
//!      template<kyosu::concepts::complex T>    constexpr auto xi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : value to process.
//!
//! **Return value**
//!
//!   Returns the Dirichlet xi sum: \f$  \displaystyle \sum_0^\infty \frac{1}{(n+1)^z}\f$
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Dirichlet series](https://en.wikipedia.org/wiki/Dirichlet_series)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/xi.cpp}
//======================================================================================================================
  inline constexpr auto xi = eve::functor<xi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto xi_(KYOSU_DELAY(), O const&, Z zz) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using u_t = eve::underlying_type_t<Z>;
      auto z = kyosu::if_else(kyosu::abs(zz) > u_t(0.25), oneminus(zz), zz); //reflection to avoid problems near zz == 1
      u_t logpi(1.1447298858494001741434273);
      auto hz = kyosu::half(kyosu::as<u_t>())*z;
      auto r = dec(z)*kyosu::tgamma(kyosu::inc(hz))*kyosu::exp(-logpi*hz)*kyosu::zeta(z);
      return r; 
    }
    else
    {
      return cayley_extend(kyosu::xi, zz);
    }
  }
}
