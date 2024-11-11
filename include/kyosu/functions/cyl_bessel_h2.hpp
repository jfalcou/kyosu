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
  struct cyl_bessel_h2_t : eve::elementwise_callable<cyl_bessel_h2_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_h2_t, cyl_bessel_h2_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_h2
//!   @brief Computes the Bessel functions of the third  kind  \f$H^{(2)}\f$,
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
//!      template<eve::floating_scalar_value N, eve::floating_ordered_value T,>
//!      constexpr auto cyl_bessel_h2(N nu, T z) noexcept;
//!
//!      template<eve::floating_scalar_value N, concepts::kyosu::complex Z>
//!      constexpr T    cyl_bessel_h2(N nu, Z z) noexcept;
//!
//!      template<eve::floating_scalar_value N, eve::floating_ordered_value T, complexRange R>
//!      constexpr auto cyl_bessel_h2(N nu, T z, R& h1s) noexcept;
//!
//!      template<eve::floating_scalar_value N, concepts::kyosu::complex Z, complexRange R>
//!      constexpr T    cyl_bessel_h2(N nu, Z z, R& h1s) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `nu`: scalar floating order of the function.
//!     * `z`: Value to process.
//!     * `h1s: range able to contain `n = int(abs(nu))+1` complex values (of type complex_t<T> or Z respectively)
//!
//!   **Return value**
//!
//!     * returns  \f$H^{(1)}_\nu(z)\f$.
//!
//!   *Ouput values
//!
//!     * on output (if present) h1s contains the values of   \f$ (H^{(1)}_{\nu_0+\epsilon i})_{i = 0 \cdots n} \f$;
//!       where \f$ \nu_0 \f$ is the fractional part of \f$\nu\f$ and \f$\epsilon\f$ is the sign of  \f$ \nu\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h2.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_h2 = eve::functor<cyl_bessel_h2_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename NU, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cyl_bessel_h2_(KYOSU_DELAY(), NU v, O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cb_h2(v, z); //cyl_bessel_j(v, z)-muli(cyl_bessel_y(v, z));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_h1, v, z);
    }
  }
}
