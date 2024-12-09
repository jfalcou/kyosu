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

namespace kyosu
{
  template<typename Options>
  struct cyl_bessel_k_t : eve::strict_elementwise_callable<cyl_bessel_k_t, Options>
  {
    template<concepts::real NU, typename Z, std::size_t S>
    requires(concepts::real<Z> || concepts::cayley_dickson<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(NU const& v, Z const & z, std::span<Z, S> ks) const noexcept
    {   return _::cb_kr(v, z, ks); }

    template<concepts::real NU, concepts::cayley_dickson Z>
    requires(eve::scalar_value<NU>)
      KYOSU_FORCEINLINE constexpr Z operator()(NU v, Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
        return _::cb_kr(v, z);
      else
        return _::cayley_extend_rev(*this, v, z);
    }

    template<concepts::real NU, concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(NU nu, V v) const noexcept
    { return  (*this)(nu, complex(v)); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_k_t, cyl_bessel_k_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_k
//!   @brief Computes the Modified Bessel functions of the second kind.
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
//!      template<eve::floating_ordered_value, kyosu::concepts::cayley_dickson T>
//!      constexpr auto cyl_bessel_k(N nu, T z) noexcept;
//!
//!      template<eve::floating_ordered_value, eve::floating_ordered_value T>
//!      constexpr T    cyl_bessel_k(N n, T z) noexcept;
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
//!     * returns \f$K_\nu(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_k.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_k = eve::functor<cyl_bessel_k_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
