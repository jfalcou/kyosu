//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct cyl_bessel_j_t : eve::strict_elementwise_callable<cyl_bessel_j_t, Options>
  {
    template<concepts::real NU, typename Z, std::size_t S>
    requires(concepts::real<Z> || concepts::cayley_dickson<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(NU const& v, Z const & z, std::span<Z, S> js) const noexcept
    {  return _::cb_jr(v, z, js); }

    template<concepts::real NU, concepts::cayley_dickson Z>
    requires(eve::scalar_value<NU>)
    KYOSU_FORCEINLINE constexpr Z operator()(NU v, Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
        return _::cb_jr(v, z);
      else
        return cayley_extend_rev(*this, v, z);
    }

    template<concepts::real NU, concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(NU nu, V v) const noexcept
    { return  (*this)(nu, complex(v)); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_j_t, cyl_bessel_j_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_j
//!   @brief Computes the Bessel functions of the first kind,
//!   \f$ J_{\nu}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+\nu +1)}}
//!   {\left({x \over 2}\right)}^{2p+\nu }\f$
//!   extended to the complex plane and cayley_dickson values.
//!
//!   It is the solution of \f$ x^{2}y''+xy'+(x^2-\nu^2)y=0\f$ for which
//!   \f$ y(0) = 0\f$ if \f$\nu \ne 0\f$ else \f$1\f$.
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
//!      template<eve::floating_scalar_value, kyosu::concepts::cayley_dickson T>
//!      constexpr auto cyl_bessel_j(N nu, T z) noexcept;
//!
//!      template<eve::floating_scalar_value, eve::floating_ordered_value T>
//!      constexpr T    cyl_bessel_j(N nu, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `nu`: order of the function.
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$J_\nu(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_j.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_j = eve::functor<cyl_bessel_j_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
