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
      return fn(v, w); }

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
//!      template< eve::floating_ordered_value T, eve::floating_ordered_value U >
//!      auto lrising_factorial(T x,U y) noexcept;                                        //1
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lrising_factorial(eve::complex_t<T> x, U y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lrising_factorial(T x, eve::complex_t<U> y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lrising_factorial(eve::complex_t<T> x, eve::complex_t<U> y) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process.
//!
//!   **Return value**
//!
//!   @brief Computes the Rising Factorial function i.e. \f$\log\frac{\Gamma(x+y)}{\Gamma(x)}\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lrising_factorial.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_lrising_factorial lrising_factorial = {};
}
