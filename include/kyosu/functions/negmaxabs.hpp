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
  struct callable_negmaxabs: eve::elementwise
  {
    using callable_tag_type = callable_negmaxabs;

    KYOSU_DEFERS_CALLABLE(negmaxabs_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const&... vs) noexcept
    {
      return eve::negmaxabs(vs...);
    }

    KYOSU_FORCEINLINE auto operator()(auto const&... targets ) const noexcept
    -> decltype(eve::tag_invoke(*this, targets...))
    {
      return eve::tag_invoke(*this, targets...);
    }

    template<typename... T>
    eve::unsupported_call<callable_negmaxabs(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var negmaxabs
//!   @brief Callable object computing the negmaxabs operation.
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
//!      template<typename ... Ts> auto negmaxabs(Ts ... zi ) const noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns elementwise  the negated maximum of the absolute values of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/negmaxabs.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_negmaxabs negmaxabs = {};
}
