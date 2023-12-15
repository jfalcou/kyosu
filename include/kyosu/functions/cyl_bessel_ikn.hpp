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
  struct callable_cyl_bessel_ikn: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_ikn;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_ikn_);

    template<eve::integral_scalar_value N, eve::floating_ordered_value T, typename R>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v, R& js, R& ys) noexcept
    {
      auto fn = callable_cyl_bessel_ikn{};
      return fn(n, complex(v), js, ys);
    }

    template<typename N, typename T, typename R>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1, R& output1, R& output2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, output1, output2))
    {
      return eve::tag_invoke(*this, target0, target1, output1, output2);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_ikn(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_ikn
//!   @brief Computes the Bessel functions of the second kind \f$I\f$ and \f$K \f$of integral order,
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
//!      constexpr auto cyl_bessel_ikn(N n, T z, R& js,  R& ys) noexcept;
//!
//!      template<eve::integral_scalar_value N, conceots::kyosu::complex Z, complexRange R>
//!      constexpr T    cyl_bessel_ikn(N n, Z z, R& js,  R& ys) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar integral order of the function.
//!     * `z`: Value to process.
//!     * `is: range able to contain int(nu)+1 complex values (of type complex_t<T> or Z respectively)
//!     * `ks: range able to contain int(nu)+1 complex values (of type complex_t<T> or Z respectively)
//!
//!   **Return value**
//!
//!     * returns the kumi pair \f$\{I_\nu(z), K_\nu(z)\}\f$.
//!
//!   *Ouput values
//!
//!     * on output is contains the values of   \f$((I_{0+i})_{i = 0\cdot n}\f$
//!     * on output ks contains the values of   \f$((K_{0+i})_{i = 0\cdot n}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_ikn.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_ikn cyl_bessel_ikn = {};
}
