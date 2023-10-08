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
  struct callable_average: eve::elementwise
  {
    using callable_tag_type = callable_average;

    KYOSU_DEFERS_CALLABLE(average_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const& v0
                                               , eve::floating_ordered_value auto const& ...v1) noexcept
    {
      return eve::average(v0, v1...);
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& ...target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1...))
    {
      return eve::tag_invoke(*this, target0, target1...);
    }

    template<typename... T>
    eve::unsupported_call<callable_average(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var average
//!   @brief Computes the average of the parameters.
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
//!     constexpr auto average(auto z0, auto... z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1...`: Values to process. Can be a mix of complex and real floating values and complex values.
//!
//!   **Return value**
//!
//!     Returns the arithmetic mean of the arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/average.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_average average = {};
}
