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
  struct callable_beta : eve::elementwise
  {
    using callable_tag_type = callable_beta;

    KYOSU_DEFERS_CALLABLE(beta_);

    template<eve::ordered_value T1, eve::ordered_value T2>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T1 const& v, T2 const& w) noexcept {
      auto fn = callable_beta{};
      return fn(to_complex(v), w); }

    template<typename T1, typename T2>
    KYOSU_FORCEINLINE auto operator()(T1 const& target1, T2 const& target2) const noexcept -> decltype(eve::tag_invoke(*this, target1, target2))
    {
      return eve::tag_invoke(*this, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_beta(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var beta
//!   @brief Computes the beta function: \f$\displaystyle \mathbf{B}(x, y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$.
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
//!      auto beta(T x,U y) noexcept;                                        //1
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto beta(eve::as_complex_t<T> x, U y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto beta(T x, eve::as_complex_t<U> y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto beta(eve::as_complex_t<T> x, eve::as_complex_t<U> y) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process.
//!
//!   **Return value**
//!
//!     1.  \f$\displaystyle \mathbf{B}(x,y) = \int_0^1 t^{x-1}(1-t)^{y-1}\mbox{d}t\f$
//!     2.  The complex \f$\displaystyle  \mathbb{B}(x,y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$ is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/beta.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_beta beta = {};
}
