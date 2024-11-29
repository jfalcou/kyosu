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
  struct cyl_bessel_h2_t : eve::strict_elementwise_callable<cyl_bessel_h2_t, Options>
  {
    template<concepts::real NU, concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(NU v, Z const& z) const noexcept
    {

      if constexpr(concepts::complex<Z> )
      {
        return _::cb_h2r(v, z);
      }
      else
      {
        return _::cayley_extend_rev(*this, v, z);
      }
    }

    template<concepts::real NU, concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(NU v, V z) const noexcept
    { return (*this)(v, complex(z)); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_h2_t, cyl_bessel_h2_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_h2
//!   @brief Computes the Bessel functions of the third  kind  (Hankel functions) \f$H_{\nu}^{(2)}\f$
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
//!     * `h1s`: range able to contain `n = int(abs(nu))+1` complex values (of type complex_t<T> or Z respectively)
//!
//!   **Return value**
//!
//!     * returns  \f$H^{(2)}_\nu(z)\f$.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: cyl_bessel_h](https://en.cppreference.com/w/cpp/numeric/special_functions/cyl_bessel_h)
//!   *  [Wikipedia: Bessel Functions](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Modified Bessel Functions](https://dlmf.nist.gov/10.2.5)
//!   *  [Wolfram: Bessel Type functions](https://functions.wolfram.com/Bessel-TypeFunctions)
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
