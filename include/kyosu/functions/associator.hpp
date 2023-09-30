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
  struct callable_associator: eve::elementwise
  {
    using callable_tag_type = callable_associator;

    KYOSU_DEFERS_CALLABLE(associator_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const& v0
                                               , eve::floating_ordered_value auto const& v1
                                               , eve::floating_ordered_value auto const& v2) noexcept
    {
      return eve::zero(eve::as(v0+v1+v2));
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1, auto const& target2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, target2))
    {
      return eve::tag_invoke(*this, target0, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_associator(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var associator
//!   @brief Computes the associator of the three parameters.
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
//!     constexpr auto associator(auto z0, auto, z1, auto, z2) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`, z2`: Values to process. Can be a mix of complex and real floating values and complex values.
//!
//!   **Return value**
//!
//!     Returns the difference z0*(z1*z2)-(z0*z1)*z2.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/associator.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_associator associator = {};
}
