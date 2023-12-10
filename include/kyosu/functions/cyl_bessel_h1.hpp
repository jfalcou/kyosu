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
  struct callable_cyl_bessel_h1: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_h1;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_h1_);

    template<eve::floating_scalar_value N, eve::floating_ordered_value T, typename R>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v, R& h1s) noexcept
    {
      auto fn = callable_cyl_bessel_h1{};
      return fn(n, complex(v), h1s);
    }

    template<eve::floating_scalar_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v) noexcept
    {
      auto fn = callable_cyl_bessel_h1{};
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
    eve::unsupported_call<callable_cyl_bessel_h1(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_h1
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
//!      template<eve::floating_scalar_value N, eve::floating_ordered_value T,>
//!      constexpr auto cyl_bessel_h1(N nu, T z) noexcept;
//!
//!      template<eve::floating_scalar_value N, concepts::kyosu::complex Z>
//!      constexpr T    cyl_bessel_h1(N nu, Z z) noexcept;
//!
//!      template<eve::floating_scalar_value N, eve::floating_ordered_value T, complexRange R>
//!      constexpr auto cyl_bessel_h1(N nu, T z, R& h1s) noexcept;
//!
//!      template<eve::floating_scalar_value N, concepts::kyosu::complex Z, complexRange R>
//!      constexpr T    cyl_bessel_h1(N nu, Z z, R& h1s) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `nu`: scalar floating order of the function.
//!     * `z`: Value to process.
//!     * `h1s: range able to contain int(nu)+1 complex values (of type complex_t<T> or Z respectively)
//!
//!   **Return value**
//!
//!     * returns  \f$\{H^{(1)}_\nu(z)\}f$.
//!
//!   *Ouput values
//!
//!     * on output (if present) h1s contains the values of   \f$((H^{(1)}_{\vu_0+i})_{i = 0\cdot n}\f$;
//!       where \f$\vu_0\f$ is the fractional part of $\vu\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h1.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_h1 cyl_bessel_h1 = {};
}
