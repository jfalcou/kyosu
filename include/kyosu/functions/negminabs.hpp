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
  struct callable_negminabs: eve::elementwise
  {
    using callable_tag_type = callable_negminabs;

    KYOSU_DEFERS_CALLABLE(negminabs_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const&... vs) noexcept
    {
      return eve::negminabs(vs...);
    }

    KYOSU_FORCEINLINE auto operator()(auto const&... targets ) const noexcept
    -> decltype(eve::tag_invoke(*this, targets...))
    {
      return eve::tag_invoke(*this, targets...);
    }

    template<typename... T>
    eve::unsupported_call<callable_negminabs(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var negminabs
//!   @brief Callable object computing the negminabs operation.
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
//!      template<typename ... Ts> auto negminabs(Ts ... zi ) const noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns elementwise  the negminimum of the absolute values of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/negminabs.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_negminabs negminabs = {};
}
