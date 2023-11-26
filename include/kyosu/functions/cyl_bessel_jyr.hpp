//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/bessel.hpp>

namespace kyosu::tags
{
  struct callable_cyl_bessel_jy: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_jy;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_jy_);

    template<eve::floating_scalar_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N nu, T const& v, R& js, R& ys) noexcept
    requires(concepts::complex<decltype(js[0]) && concepts::complex<decltype(ys[0]))
    {
      auto fnu = callable_cyl_bessel_jy{};
      return fnu(nu, complex(v), js, ys);
    }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1, R& output1, R& output2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, output1, output2))
    {
      return eve::tag_invoke(*this, target0, target1, output1, output2);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_jy(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_jyr
//!   @brief Computes the Bessel functions of the first kind J and Y,
//!   \f$ J_{\nu}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+\nu +1)}}
//!   {\left({x \over 2}\right)}^{2p+\nu }\f$
//!   extended to the complex plane.
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
//!      template<eve::floating_scalar_ordered_value N, eve::floating_ordered_value T, complexRange R>
//!      constexpr auto cyl_bessel_jyr(N nu, T z, R& js,  R& ys) noexcept;
//!
//!      template<eve::floating_scalar_ordered_value N, conceots::kyosu::complex Z, complexRange R>
//!      constexpr T    cyl_bessel_jyr(N n, Z z, R& js,  R& ys) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `nu`: scalar order of the function not necessarily integral.
//!     * `z`: Value to process.
//!     * `js: range able to contain int(nu)+1 complex values (of type complex_t<T> or Z respectively)
//!     * `ys: range able to contain int(nu)+1 complex values (of type complex_t<T> or Z respectively)
//!
//!   **Return value**
//!
//!     * returns the kumi pair \f$\{J_\nu(z), Y_\nu(z)\}f$ of complex values.
//!
//!   *Ouput values
//!
//!     * on output js contains the values of   \f$((J_{\nu_0+i})_{i = 0\cdot n}\f$
//!     * on output ys contains the values of   \f$((Y_{\nu_0+i})_{i = 0\cdot n}\f$
//!
//!        where \f$\nu_0\f$ is the fractional part of \f$\nu\f$ (\f$0 \le\nu_0\lt 0\f$ and \f$\nu = \nu_0+n\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_jyr.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_jyr cyl_bessel_jyr = {};
}
