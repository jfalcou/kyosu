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
  struct callable_log_gamma : eve::elementwise
  {
    using callable_tag_type = callable_log_gamma;

    KYOSU_DEFERS_CALLABLE(log_gamma_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept {
      auto fn = callable_log_gamma{};
      return fn(complex(v)); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_log_gamma(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log_gamma
//!   @brief Computes the log of the \f$\Gamma\f$ function.
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
//!      constexpr auto  log_gamma(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns \f$\log(\Gamma(z))\f$. If z is floating the result is as if complex(z) was used in the call.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log_gamma.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_log_gamma log_gamma = {};
}
