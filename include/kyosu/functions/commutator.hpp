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
  struct callable_commutator: eve::elementwise
  {
    using callable_tag_type = callable_commutator;

    KYOSU_DEFERS_CALLABLE(commutator_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const& v0
                                               , eve::floating_ordered_value auto const& v1) noexcept
    {
      return eve::zero(eve::as(v0+v1));
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_commutator(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var commutator
//!   @brief Computes the commutator of the two parameters.
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
//!     constexpr auto commutator(auto z0, auto, z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process. Can be a mix of complex and real floating values and complex values.
//!
//!   **Return value**
//!
//!     Returns the difference z0*z1-z1*z0.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/commutator.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_commutator commutator = {};
}
