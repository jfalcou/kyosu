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
  struct callable_hypot : eve::elementwise
  {
    using callable_tag_type = callable_hypot;

    KYOSU_DEFERS_CALLABLE(hypot_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const&... vs) noexcept
    {
      return eve::hypot(vs...);
    }

    KYOSU_FORCEINLINE auto operator()(auto const&... targets ) const noexcept
    -> decltype(eve::tag_invoke(*this, targets...))
    {
      return eve::tag_invoke(*this, targets...);
    }

    template<typename... T>
    eve::unsupported_call<callable_hypot(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var hypot
//!   @brief Callable object computing the hypot operation.
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
//!      template< f typename ... Ts> auto hypot(Ts ... zi ) const noexcept
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * ` zi...` : Values to process: mix of floating and Cayley-Dickson.
//!
//!   **Return value**
//!
//!     *  Returns \f$ \sqrt{\sum_{i = 0}^{n-1} |z_i|^2} \f$ where \f$n\f$ is the number of arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/hypot.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_hypot hypot = {};
}
