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
  struct callable_cyl_bessel_h2: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_h2;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_h2_);

    template<eve::floating_scalar_value N, eve::floating_ordered_value T, typename R>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v, R& h2s) noexcept
    {
      auto fn = callable_cyl_bessel_h2{};
      return fn(n, complex(v), h2s, h2s);
    }

    template<eve::floating_scalar_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v) noexcept
    {
      auto fn = callable_cyl_bessel_h2{};
      return fn(n, complex(v));
    }

    template<typename N, typename T, typename R>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1, R& output1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, output1))
    {
      return eve::tag_invoke(*this, target0, target1, output1);
    }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

                template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_h2(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_h2
//!   @brief Computes the Bessel functions of the third  kind \f$ H^{(2)}_\nu \f$,
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
//!      constexpr auto cyl_bessel_h2(N nu, T z, R& h2s) noexcept;
//!
//!      template<eve::floating_scalar_value N, concepts::kyosu::complex Z, complexRange R>
//!      constexpr T    cyl_bessel_h2(N nu, Z z, R& h2s) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `nu`: scalar floating order of the function.
//!     * `z`: Value to process.
//!     * `h2s: range able to contain `n = int(abs(nu))+1` complex values (of type complex_t<T> or Z respectively)
//!
//!   **Return value**
//!
//!     * returns  \f$H^{(2)}_\nu(z)\f$.
//!
//!   *Ouput values
//!
//!     * on output (if present) h2s contains the values of   \f$ (H^{(2)}_{\nu_0+\epsilon i})_{i = 0 \cdots n} \f$,
//!       where \f$ \nu_0 \f$ is the fractional part of \f$\nu\f$ and \f$\epsilon\f$ is the sign of  \f$ \nu\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h2.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_h2 cyl_bessel_h2 = {};
}
