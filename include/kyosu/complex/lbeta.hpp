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
  struct callable_lbeta : eve::elementwise
  {
    using callable_tag_type = callable_lbeta;

    KYOSU_DEFERS_CALLABLE(lbeta_);

    template<eve::ordered_value T, eve::ordered_value U>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v, U const& w) noexcept {
      auto fn = callable_lbeta{};
      return fn(to_complex(v), w); }

    template<typename T, typename U>
    KYOSU_FORCEINLINE auto operator()(T const& target1, U const& target2) const noexcept -> decltype(eve::tag_invoke(*this, target1, target2))
    {
      return eve::tag_invoke(*this, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_lbeta(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lbeta
//!   @brief Computes the natural logarithm of the lbeta function.
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
//!      auto lbeta(T x,U y) noexcept;                                        //1
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lbeta(eve::complex_t<T> x, U y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lbeta(T x, eve::complex_t<U> y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lbeta(eve::complex_t<T> x, eve::complex_t<U> y) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process.
//!
//!   **Return value**
//!
//!    `log(beta(x, y)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lbeta.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_lbeta lbeta = {};
}
