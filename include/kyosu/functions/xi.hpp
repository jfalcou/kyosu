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
#include <kyosu/functions/tgamma.hpp>
#include <kyosu/functions/if_else.hpp>

namespace kyosu
{
  template<typename Options>
  struct xi_t : eve::elementwise_callable<xi_t, Options,  riemann_option, landau_option>
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
//!   @brief Computes the Riemann \f$ \displaystyle\xi(z) = \frac{1}{2}z(z-1)\pi^{-\frac{z}{2}}\Gamma(\frac{z}{2})\zeta(z)\f$.
//!   function or the Landau  version  \f$ \displaystyle\Xi(z) = \xi(\frac{1}{2} + i z)\f$.
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
//!      //regular call
//!      constexpr auto xi(auto z) noexcept;           // 1
//!
//!      // Semantic modifyiers
//!      constexpr auto xi[riemann](auto z) noexcept;  // 1
//!      constexpr auto xi[landau](T z) noexcept;      // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : cayley-dickson like value to process.
//!
//! **Return value**
//!
//!   1. Returns the value at `z` of the Riemann  \f$\xi\f$ function (ξ can be used a an alias).
//!   3. Returns the value at `z` of the Landau   \f$\Xi\f$ function (Ξ can be used a an alias).
//!
//!   if the input `z` is a floating_value the call is done as if `complex(z)` was input.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Riemann xi function](https://en.wikipedia.org/wiki/Riemann_xi_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/xi.cpp}
//======================================================================================================================
  inline constexpr auto xi = eve::functor<xi_t>;
  inline constexpr auto Ξ = xi[landau];
  inline constexpr auto ξ = xi[riemann];
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto xi_(KYOSU_DELAY(), O const& o, Z zz) noexcept
  {
    if constexpr(O::contains(landau))
      return xi(kyosu::half(as(zz))+kyosu::muli(zz));
    else if constexpr(concepts::complex<Z> )
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
      return cayley_extend(kyosu::xi[o], zz);
    }
  }
}
