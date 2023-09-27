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
  struct callable_pow_abs : eve::elementwise
  {
    using callable_tag_type = callable_pow_abs;

    KYOSU_DEFERS_CALLABLE(pow_abs_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const& v0
                                               , eve::floating_ordered_value auto const& v1) noexcept
    {
      return eve::pow(eve::abs(v0), v1);
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_pow_abs(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow_abs
//!   @brief Computes the  computing the pow_abs operation \f$(|x|)^y\f$.
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
//!      template<kyosu::concepts::cayley_dickson T0, kyosu::concepts::cayley_dickson T1 > constexpr auto pow_abs(T0 z0, T1, z1) noexcept;
//!      template<eve::floating_ordered_value T0, kyosu::concepts::cayley_dickson T1>             > constexpr auto pow_abs(T0 z0, T1, z1) noexcept;
//!      template<kyosu::concepts::cayley_dickson T0,  eve::floating_ordered_value T1             > constexpr auto pow_abs(T0 z0, T1, z1) noexcept;
//!      template<eve::floating_ordered_value T0, floating_ordered_value T1>                               > constexpr auto pow_abs(T0 z0, T1, z1) noexcept;
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1` : Values to process.
//!
//!   **Return value**
//!
//!      the call is semantically equivalent to `eve::exp(abs(z1)*log(z0))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow_abs.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_pow_abs pow_abs = {};
}
