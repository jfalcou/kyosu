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
  struct callable_ldiv : eve::elementwise
  {
    using callable_tag_type = callable_ldiv;

    KYOSU_DEFERS_CALLABLE(ldiv_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::ordered_value auto const& v0
                                               , eve::ordered_value auto const& v1) noexcept
    {
      return v1/v0;
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_ldiv(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var ldiv
//!   @brief Computes the left division of the two parameters.
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
//!      template<kyosu::concepts::cayley_dickson T0, kyosu::concepts::cayley_dickson T1 > constexpr auto ldiv(T0 z0, T1, z1) noexcept;
//!      template<eve::ordered_value T0, kyosu::concepts::cayley_dickson T1>             > constexpr auto ldiv(T0 z0, T1, z1) noexcept;
//!      template<kyosu::concepts::cayley_dickson T0,  eve::ordered_value T1             > constexpr auto ldiv(T0 z0, T1, z1) noexcept;
//!      template<eve::ordered_value T0, ordered_value T1>                               > constexpr auto ldiv(T0 z0, T1, z1) noexcept;
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1` : Values to process.
//!
//!   **Return value**
//!
//!     Returns the left division  of the two arguments. This function not equivalent to z1/z0 as soon as multiplication
//!     is not commutative.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/ldiv.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_ldiv ldiv = {};
}
