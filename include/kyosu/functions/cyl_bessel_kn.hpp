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
  struct cyl_bessel_kn_t : eve::strict_elementwise_callable<cyl_bessel_kn_t, Options>
  {
    template<eve::integral_scalar_value Z0, typename Z1, std::size_t S>
    requires(concepts::real<Z1> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& n, Z1 const & z, std::span<Z1, S> ks) const noexcept
    {
      auto doit = [n, z, &ks](auto is){
        _::cb_ikn(n, z, is, ks);
      };
      _::with_alloca<Z1>(eve::abs(n)+1, doit);
      return ks[n];
    }

    template<eve::integral_scalar_value Z0, concepts::cayley_dickson Z1>
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& n, Z1 const & z) const noexcept
    {
      if constexpr(concepts::complex<Z1> )
      {
        return _::cb_kn(n, z);
      }
      else
      {
        return _::cayley_extend_rev(*this, n, z);
      }
    }

    template<eve::integral_scalar_value V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept
    { return (*this)(v0,v1); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_kn_t, cyl_bessel_kn_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_kn
//!   @brief Computes the modified Bessel functions of the second kind,
//!   \f$ Y_n(x)=\lim_{\alpha\to n}{{\frac {J_{\alpha  }(x)\cos(\alpha\pi)-J_{-\alpha }(x)}{\sin(\alpha\pi)}}}\f$,
//!   extended to the complex plane and cayley_dickson algebras.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_kn(int n, T z) noexcept;
//!      template<kyosu::concepts::complex T>        constexpr auto cyl_bessel_kn(int n, T z, std::span<T> js)  noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    cyl_bessel_kn(int n, T z) noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    cyl_bessel_kn(int n, T z, std::span<T> js)) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar integral order
//!     * `z`: Value to process.
//!     * `ys': span allocated for 'n+1' values of type 'T'
//!
//!   **Return value**
//!
//!     * returns \f$Y_n(z)\f$,  and if the 'span' parameter is present it must be sufficient to hold 'n+1' values which are
//!       \f$(y_0(x), y_1(x), ...,  y_n(x))\f$ if 'n >= 0$ else \f$(y_0(x),y_{-1}(x) ...,  y_{-n}(x)\f$ (for the same computation cost),
//!       but use is restricted to real or complex entries.
//!//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_kn.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_kn = eve::functor<cyl_bessel_kn_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
