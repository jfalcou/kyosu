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
  struct callable_lpnorm : eve::elementwise
  {
    using callable_tag_type = callable_lpnorm;

    KYOSU_DEFERS_CALLABLE(lpnorm_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const& p
                                               , eve::floating_ordered_value auto const&... vs) noexcept
    {
      return eve::lpnorm(p, vs...);
    }

    KYOSU_FORCEINLINE auto operator()(auto const&... targets ) const noexcept
    -> decltype(eve::tag_invoke(*this, targets...))
    {
      return eve::tag_invoke(*this, targets...);
    }

    template<typename... T>
    eve::unsupported_call<callable_lpnorm(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lpnorm
//!   @brief Callable object computing the lpnorm operation \f$ \left(\sum_{i = 0}^n
//! |x_i|^p\right)^{\frac1p} \f$.
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
//!      template< floating_value P, typename T, typename ... Ts> auto operator()(P p, T z,Ts ... zs ) const noexcept
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `p`:    : positive floating ordered value
//!     * `zs...` : Values to process.
//!
//!   **Return value**
//!
//!     Returns \f$ \left(\sum_{i = 0}^n |x_i|^p\right)^{\frac1p} \f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lpnorm.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_lpnorm lpnorm = {};
}
