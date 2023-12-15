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
  struct callable_cyl_bessel_ik: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_ik;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_ik_);

    template<eve::floating_scalar_value N, eve::floating_ordered_value T, typename R1, typename R2>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N nu, T const& v, R1& is, R2& ks) noexcept
    requires(concepts::complex<decltype(is[0])> && concepts::complex<decltype(ks[0])>)
    {
      auto fnu = callable_cyl_bessel_ik{};
      return fnu(nu, complex(v), is, ks);
    }

    template<typename N, typename T, typename R1, typename R2>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1, R1& output1, R2& output2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, output1, output2))
    {
      return eve::tag_invoke(*this, target0, target1, output1, output2);
    }

//     template<typename... T>
//     eve::unsupported_call<callable_cyl_bessel_ik(T&&...)> operator()(T&&... x) const
//     requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_ik
//!   @brief Computes the modified Bessel functions \f$I\f$ and \f$K\f$,
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
//!      constexpr auto cyl_bessel_ik(N nu, T z, R& js,  R& ys) noexcept;
//!
//!      template<eve::floating_scalar_ordered_value N, conceots::kyosu::complex Z, complexRange R>
//!      constexpr T    cyl_bessel_ik(N n, Z z, R& js,  R& ys) noexcept;
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
//!     * returns the kumi pair \f$\{I_\nu(z), K_\nu(z)\}\f$ of complex values.
//!
//!   *Ouput values
//!
//!     * on output js contains the values of   \f$((I_{\nu_0+\epsilon i})_{i = 0\cdot n}\f$
//!     * on output ys contains the values of   \f$((K_{\nu_0+\epsilon i})_{i = 0\cdot n}\f$
//!
//!        where \f$\nu_0\f$ is the fractional part of \f$\nu\f$, \f$\nu = \nu_0+\epsilon n\f$
//!        and  \f$\epsilon\f$ is the sign of \f$\nu\f$ .
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_ik.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_ik cyl_bessel_ik = {};
}
