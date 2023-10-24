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
  struct callable_lrising_factorial : eve::elementwise
  {
    using callable_tag_type = callable_lrising_factorial;

    KYOSU_DEFERS_CALLABLE(lrising_factorial_);

    template<eve::ordered_value T1, eve::ordered_value T2>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T1 const& v, T2 const& w) noexcept {
      auto fn = callable_lrising_factorial{};
      return fn(complex(v), complex(w)); }

    template<typename T1, typename T2>
    KYOSU_FORCEINLINE auto operator()(T1 const& target1, T2 const& target2) const noexcept -> decltype(eve::tag_invoke(*this, target1, target2))
    {
      return eve::tag_invoke(*this, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_lrising_factorial(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lrising_factorial
//!   @brief Computes the lrising_factorial function: \f$\log\frac{\Gamma(x+y)}{\Gamma(x)}\f$.
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
//!      auto lrising_factorial(auto x,auto y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process.
//!
//!   **Return value**
//!
//!   @brief Computes the logarithm of rising Factorial i.e. \f$\log\frac{\Gamma(x+y)}{\Gamma(x)}\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lrising_factorial.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_lrising_factorial lrising_factorial = {};
}
