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
  struct callable_pow : eve::elementwise
  {
    using callable_tag_type = callable_pow;

    KYOSU_DEFERS_CALLABLE(pow_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const& v0
                                               , eve::floating_ordered_value auto const& v1) noexcept
    {
      return eve::pow(v0, v1);
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_pow(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow
//!   @brief Computes the  computing the pow operation \f$x^y\f$.
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
//!      template<kyosu::concepts::cayley_dickson T0, kyosu::concepts::cayley_dickson T1 > constexpr auto pow(T0 z0, T1, z1) noexcept;
//!      template<eve::floating_ordered_value T0, kyosu::concepts::cayley_dickson T1>             > constexpr auto pow(T0 z0, T1, z1) noexcept;
//!      template<kyosu::concepts::cayley_dickson T0,  eve::floating_ordered_value T1             > constexpr auto pow(T0 z0, T1, z1) noexcept;
//!      template<eve::floating_ordered_value T0, floating_ordered_value T1>                               > constexpr auto pow(T0 z0, T1, z1) noexcept;
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1` : Values to process.
//!
//!   **Return value**
//!
//!      the call is semantically equivalent to `eve::exp(z1*eve::log(z0))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_pow pow = {};
}
