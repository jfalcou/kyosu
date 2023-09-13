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
  struct callable_tgamma : eve::elementwise
  {
    using callable_tag_type = callable_tgamma;

    KYOSU_DEFERS_CALLABLE(tgamma_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept {
      auto fn = callable_tgamma{};
      return fn(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_tgamma(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tgamma
//!   @brief Computes the tgammaolute value of the parameter.
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
//!      template<kyosu::concepts::complex T>   constexpr T  tgamma(T z) noexcept;
//!      template<eve::floatingordered_value T> constexpr T  tgamma(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns \f$\Gamma(z)\f$. If z is floating the result is as if to_complex(z) was used in the call.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/tgamma.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_tgamma tgamma = {};
}
