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
#include <kyosu/bessel.hpp>

namespace kyosu
{
  template<typename Options>
  struct cyl_bessel_yn_t : eve::strict_elementwise_callable<cyl_bessel_yn_t, Options>
  {
    template<eve::integral_scalar_value Z0, typename Z1, std::size_t S>
    requires(concepts::real<Z1> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1, std::span<Z1, S> ys) const noexcept
    { return KYOSU_CALL(z0,z1,ys); }

    template<eve::integral_scalar_value Z0, concepts::cayley_dickson Z1>
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept
    { return KYOSU_CALL(z0,z1); }

    template<eve::integral_scalar_value V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept
    { return KYOSU_CALL(v0,v1); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_yn_t, cyl_bessel_yn_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_yn
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_yn(int n, T z) noexcept;
//!      template<kyosu::concepts::complex T>        constexpr auto cyl_bessel_yn(int n, T z, std::span<T> js)  noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    cyl_bessel_yn(int n, T z) noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    cyl_bessel_yn(int n, T z, std::span<T> js)) noexcept;
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
//!  @godbolt{doc/cyl_bessel_yn.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_yn = eve::functor<cyl_bessel_yn_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename N, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cyl_bessel_yn_(KYOSU_DELAY(), O const&, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto doit = [n, z](auto js, auto ys){
       auto [_, yn] =  cb_jyn(n, z, js, ys);
        return yn;
      };
      return with_alloca<Z>(eve::abs(n)+1, doit);
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_yn, n, z);
    }
  }

  template<typename N, typename Z, std::size_t S, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cyl_bessel_yn_(KYOSU_DELAY(), O const&, N n, Z z
                                                 , std::span<Z, S> ys) noexcept
  {
    auto doit = [n, z, &ys](auto js){
      cb_jyn(n, z, js, ys);
    };
    with_alloca<Z>(eve::abs(n)+1, doit);
    return ys[n];
  }
}
