//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_polar : eve::elementwise
  {
    using callable_tag_type = callable_polar;

    KYOSU_DEFERS_CALLABLE(polar_);

    template<eve::ordered_value T0, eve::ordered_value T1>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T0 const& rho, T1 const & theta) noexcept
    {
      auto [s, c] = eve::sincos(theta);
      return kyosu::complex(rho*c, eve::if_else(eve::is_eqz(s), eve::zero, rho*s));
    }

    template<typename T0, typename T1>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0, T1 const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0,  target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_polar(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var polar
//!   @brief complex number from modulus and argument.
//!
//!   **Defined in Header**
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
//!      template<eve::ordered_value T0, eve::ordered_value T1> constexpr auto polar(T0 rho, T1 theta) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `rho` : modulus.
//!     * `theta` : argument.
//!
//!   **Return value**
//!
//!     Returns elementwise true the polarument of the complex number i.e. \f$\rho e^{i\theta}\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/polar.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_polar polar = {};
}
