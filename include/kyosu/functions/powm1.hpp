//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/math.hpp>
namespace kyosu::tags
{
  struct callable_powm1 : eve::elementwise
  {
    using callable_tag_type = callable_powm1;

    KYOSU_DEFERS_CALLABLE(powm1_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::ordered_value auto const& v0
                                               , eve::ordered_value auto const& v1) noexcept
    {
      return eve::powm1(v0, v1); //dec(eve::pow(v0, v1));
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_powm1(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var powm1
//!   @brief Computes the  computing the powm1 operation \f$x^y-1\f$.
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
//!      template<kyosu::concepts::cayley_dickson T0, kyosu::concepts::cayley_dickson T1 > constexpr auto powm1(T0 z0, T1, z1) noexcept;
//!      template<eve::ordered_value T0, kyosu::concepts::cayley_dickson T1>             > constexpr auto powm1(T0 z0, T1, z1) noexcept;
//!      template<kyosu::concepts::cayley_dickson T0,  eve::ordered_value T1             > constexpr auto powm1(T0 z0, T1, z1) noexcept;
//!      template<eve::ordered_value T0, ordered_value T1>                               > constexpr auto powm1(T0 z0, T1, z1) noexcept;
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1` : Values to process.
//!
//!   **Return value**
//!
//!      the call is semantically equivalent to `eve::exp(z1*eve::log(z0))-1`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/powm1.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_powm1 powm1 = {};
}
