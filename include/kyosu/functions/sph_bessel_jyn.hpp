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
  struct callable_sph_bessel_jyn: eve::elementwise
  {
    using callable_tag_type = callable_sph_bessel_jyn;

    KYOSU_DEFERS_CALLABLE(sph_bessel_jyn_);

    template<eve::integral_scalar_value N, eve::floating_ordered_value T, typename R1, typename R2>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v, R1& js, R2& ys) noexcept
    //    requires(concepts::complex<decltype(js[0])> && concepts::complex<decltype(ys[0])>)
    {
      auto fn = callable_sph_bessel_jyn{};
      return fn(n, complex(v), js, ys);
    }

    template<typename N, typename T, typename R1, typename R2>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1, R1& output1, R2& output2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, output1, output2))
    {
      return eve::tag_invoke(*this, target0, target1, output1, output2);
    }

    template<typename... T>
    eve::unsupported_call<callable_sph_bessel_jyn(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_jyn
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
//!      template<eve::integral_scalar_value N, eve::floating_ordered_value T, complexRange R>
//!      constexpr auto sph_bessel_jyn(N n, T z, R& js,  R& ys) noexcept;
//!
//!      template<eve::integral_scalar_value N, conceots::kyosu::complex Z, complexRange R>
//!      constexpr T    sph_bessel_jyn(N n, Z z, R& js,  R& ys) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar integral order of the function.
//!     * `z`: Value to process.
//!     * `js: range able to contain int(nu)+1 complex values (of type complex_t<T> or Z respectively)
//!     * `ys: range able to contain int(nu)+1 complex values (of type complex_t<T> or Z respectively)
//!
//!   **Return value**
//!
//!     * returns the kumi pair \f$\{J_\nu(z), Y_\nu(z)\}f$.
//!
//!   *Ouput values
//!
//!     * on output js contains the values of   \f$((J_{0+i})_{i = 0\cdot n}\f$
//!     * on output ys contains the values of   \f$((Y_{0+i})_{i = 0\cdot n}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_jyn.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sph_bessel_jyn sph_bessel_jyn = {};
}
