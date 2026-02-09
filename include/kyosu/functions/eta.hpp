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
#include <kyosu/functions/deta.hpp>

namespace kyosu
{
  template<typename Options> struct eta_t : eve::elementwise_callable<eta_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      return deta(1u, z);
    }

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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto eta(T z) noexcept;
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
  //!  @note η can be used as an alias in code.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/eta.cpp}
  //======================================================================================================================
  inline constexpr auto eta = eve::functor<eta_t>;
  inline constexpr auto η = eve::functor<eta_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
