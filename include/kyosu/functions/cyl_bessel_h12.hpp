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
  struct callable_cyl_bessel_h12: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_h12;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_h12_);

    template<eve::floating_scalar_value N, eve::floating_ordered_value T, typename R1, typename R2>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v, R1& h1s, R2& h2s) noexcept
    {
      auto fn = callable_cyl_bessel_h12{};
      return fn(n, complex(v), h1s, h2s);
    }

    template<typename N, typename T, typename R1, typename R2>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1, R1& output1, R2& output2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, output1, output2))
    {
      return eve::tag_invoke(*this, target0, target1, output1, output2);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_h12(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_h12
//!   @brief Computes the Bessel functions of the third  kind \f$ H^{(1)} \f$ and \f$ H^{(2)} \f$,
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
//!      template<eve::floating_scalar_value N, eve::floating_ordered_value T, complexRange R1, complexRange R2>
//!      constexpr auto cyl_bessel_h12(N nu, T z, R1& h1s,  R2& h2s) noexcept;
//!
//!      template<eve::floating_scalar_value N, conceots::kyosu::complex Z, complexRange R1, complexRange R2>
//!      constexpr T    cyl_bessel_h12(N nu, Z z, R1& h1s,  R2& h2s) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar floating order of the function.
//!     * `z`: Value to process.
//!     * `h1s: range able to contain  `n = int(abs(nu))+1` complex values (of type complex_t<T> or Z respectively)
//!     * `h2s: range able to contain  `n = int(abs(nu))+1` complex values (of type complex_t<T> or Z respectively)
//!
//!   **Return value**
//!
//!     * returns the kumi pair \f$ \{ H^{(1)}_\nu(z). H^{(2)}_\nu(z) \} \f$.
//!
//!   *Ouput values
//!
//!     * on output (if present) h1s and h2s contains the values of   \f$ (H^{(1\|2)}_{\nu_0+\epsilon i})_{i = 0 \cdots n} \f$
//!       respectively,  where \f$ \nu_0 \f$ is the fractional part of \f$\nu\f$ and \f$\epsilon\f$ is the sign of  \f$ \nu\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h12.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_h12 cyl_bessel_h12 = {};
}
