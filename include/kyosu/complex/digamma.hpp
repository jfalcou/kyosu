//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/special.hpp>

namespace kyosu::tags
{
  struct callable_digamma : eve::elementwise
  {
    using callable_tag_type = callable_digamma;

    KYOSU_DEFERS_CALLABLE(digamma_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::digamma(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_digamma(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var digamma
//!   @brief Computes the Digamma function i.e. the logarithmic derivative of the \f$\Gamma\f$
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
//!      template<kyosu::concepts::complex T>   constexpr T  digamma(T z) noexcept;
//!      template<eve::floatingordered_value T> constexpr T  digamma(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     The value of the Digamma function: \f$\frac{\Gamma'(z)}{\Gamma(z)}\f$ is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/digamma.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_digamma digamma = {};
}
