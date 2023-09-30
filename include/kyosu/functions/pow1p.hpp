//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
namespace kyosu::tags
{
  struct callable_pow1p: eve::elementwise
  {
    using callable_tag_type = callable_pow1p;

    KYOSU_DEFERS_CALLABLE(pow1p_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const& v0
                                               , eve::floating_ordered_value auto const& v1) noexcept
    {
      return eve::pow1p(v0, v1);
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_pow1p(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow1p
//!   @brief Computes the  computing the pow1p operation \f$(x+1)^y\f$.
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
//!     constexpr auto average(auto z0, auto, z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1`: Values to process.
//!
//!   **Return value**
//!
//!      the call is semantically equivalent to `pow(inc(z))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow1p.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_pow1p pow1p = {};
}
