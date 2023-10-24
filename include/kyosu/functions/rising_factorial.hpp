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
  struct callable_rising_factorial : eve::elementwise
  {
    using callable_tag_type = callable_rising_factorial;

    KYOSU_DEFERS_CALLABLE(rising_factorial_);

    template<eve::ordered_value T1, eve::ordered_value T2>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T1 const& v, T2 const& w) noexcept {
      auto fn = callable_rising_factorial{};
      return fn(complex(v), complex(w)); }

    template<typename T1, typename T2>
    KYOSU_FORCEINLINE auto operator()(T1 const& target1, T2 const& target2) const noexcept -> decltype(eve::tag_invoke(*this, target1, target2))
    {
      return eve::tag_invoke(*this, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_rising_factorial(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var rising_factorial
//!   @brief Computes the rising_factorial function: \f$\frac{\Gamma(x+y)}{\Gamma(x)}\f$.
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
//!      constexpr auto rising_factorial(auto x,auto y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process.
//!
//!   **Return value**
//!
//!   @brief Computes the rising Factorial i.e. \f$\frac{\Gamma(x+y)}{\Gamma(x)}\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/rising_factorial.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_rising_factorial rising_factorial = {};
}
