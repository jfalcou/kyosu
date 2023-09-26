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
  struct callable_arg : eve::elementwise
  {
    using callable_tag_type = callable_arg;

    KYOSU_DEFERS_CALLABLE(arg_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept {
      return eve::if_else(eve::is_positive(v), eve::zero, eve::pi(eve::as(v)));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_arg(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var arg
//!   @brief complex number argument.
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
//!      template<eve::ordered_value T>              constexpr auto arg(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr auto arg(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto arg(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     1. Returns 0 or pi acording to the non negativity of z.
//!     2. Returns elementwise the argument of the complex number i.e. `atan2(imag(z), real(z))`.
//!     3. Returns \f$\mathrm{atan2}(|\underline{z}|, z_0)\f$ where \f$z_0\f$ is the real part of \f$z\f$ and
//!         \f$\underline{z}\f$ is the pure part of \f$z\f$.

//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/arg.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_arg arg = {};
}
