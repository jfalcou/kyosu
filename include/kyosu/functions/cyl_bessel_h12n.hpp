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
  struct callable_cyl_bessel_h12n: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_h12n;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_h12n_);

    template<eve::integral_scalar_value N, eve::floating_ordered_value T, typename R>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v, R& js, R& ys) noexcept
    //    requires(concepts::complex<decltype(js[0])> && concepts::complex<decltype(ys[0])>)
    {
      auto fn = callable_cyl_bessel_h12n{};
      return fn(n, complex(v), js, ys);
    }

    template<typename N, typename T, typename R>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1, R& output1, R& output2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, output1, output2))
    {
      return eve::tag_invoke(*this, target0, target1, output1, output2);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_h12n(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_h12n
//!   @brief Computes the Bessel functions of the third  kind \f$H^{(1)\f$ and \f$H^{(2)}\f$,
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
//!      constexpr auto cyl_bessel_h12n(N n, T z, R& h1s,  R& h2s) noexcept;
//!
//!      template<eve::integral_scalar_value N, conceots::kyosu::complex Z, complexRange R>
//!      constexpr T    cyl_bessel_h12n(N n, Z z, R& h1s,  R& h2ss) noexcept;
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
//!  @godbolt{doc/cyl_bessel_h12n.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_h12n cyl_bessel_h12n = {};
}
