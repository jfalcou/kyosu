//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/bessel.hpp>

namespace kyosu
{
  template<typename Options>
  struct cyl_bessel_h12_t : eve::strict_elementwise_callable<cyl_bessel_h12_t, Options>
  {
    template<concepts::real NU, typename Z, std::size_t S>
    requires(concepts::real<Z> || concepts::cayley_dickson<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(NU const& v, Z const & z,
                                                   std::span<Z, S> h1s, std::span<Z, S> h2s) const noexcept
    {   return _::cb_h12r(v, z, h1s, h2s); }
    
    template<concepts::real NU, concepts::cayley_dickson Z>
    requires(eve::scalar_value<NU> && (concepts::real<Z> || concepts::cayley_dickson<Z>))
      KYOSU_FORCEINLINE constexpr auto  operator()(NU const& v, Z const & z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        auto doit = [v, z](auto h1s, auto h2s){
          return _::cb_h12r(v, z, h1s, h2s);
        };
        return with_alloca<Z>(eve::abs(v)+1, doit);
      }
      else
        return caley_extend_rev2(*this, v, z);
    }
    
    KYOSU_CALLABLE_OBJECT(cyl_bessel_h12_t, cyl_bessel_h12_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_h12
//!   @brief Computes the Hankel functions of the first and second kind,
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
//!      template<kyosu::concepts::cayley_dickson T constexpr auto cyl_bessel_h12(eve::floating_scalar_value n, T z) noexcept;
//!      template<kyosu::concepts::complex T        constexpr auto cyl_bessel_h12(eve::floating_scalar_value n, T z
//!                                                                            , std::span<T> h1s, std::span<T> h2s) noexcept;
//!      template<kyosu::concepts::real T>          constexpr auto cyl_bessel_h12(eve::floating_scalar_value n, T z) noexcept;
//!      template<kyosu::concepts::real T>          constexpr auto cyl_bessel_h12(eve::floating_scalar_value n, T z
//!                                                                            , std::span<T> h1s, std::span<T> h2s) noexcept;
//!   }
//!   @endcode
//!
//!     * `nu`: scalar floating order of the function.
//!     * `z`: Value to process.
//!     * `h1s`: range able to contain `n = int(abs(nu))+1` values (of type T)
//!     * `h2s`: range able to contain `n = int(abs(nu))+1` values (of type T)
//!
//!   **Return value**
//!
//!     * returns  a kumi tupler containing \f$h1n(z)\f$ and \f$h2n(z)\f$ and if the 'span' parameters are present
//!       ithey  must be sufficient to hold 'n+1' values each which are respectively
//!        \$(h1_0(x), h1_1(x), ...,  h1_n(x))\f$ if 'n >= 0$ else \$(h1_0(x),h1_{-1}(x) ...,  h1_{-n}(x)\f$ (for the same computation cost),
//!       and  \$(h2_0(x), h2_1(x), ...,  h2_n(x))\f$ if 'n >= 0$ else \$(h2_0(x),h2_{-1}(x) ...,  h2_{-n}(x)\f$ (for the same computation cost),
//!       but use is restricted to real or complex entries..
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: cyl_bessel_h](https://en.cppreference.com/w/cpp/numeric/special_functions/cyl_bessel_h)
//!   *  [Wikipedia: Bessel Functions](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Modified Bessel Functions](https://dlmf.nist.gov/10.2.5)
//!   *  [Wolfram: Bessel Type functions](https://functions.wolfram.com/Bessel-TypeFunctions)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h12.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_h12 = eve::functor<cyl_bessel_h12_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
