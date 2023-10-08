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
      return fn(complex(v), w); }

    template<typename T1, typename T2>
    KYOSU_FORCEINLINE auto operator()(T1 const& target1, T2 const& target2) const noexcept
    -> decltype(eve::tag_invoke(*this, target1, target2))
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
//!   @brief Computes the beta function: \f$\displaystyle \mathbf{B}(x, y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$
//!   for real or complex entries.
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
//!      auto beta(auto x, auto y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process. Can be a mix of complex and real floating values and complex values.
//!
//!   **Return value**
//!
//!     1.  If x and y are real typed values returns \f$\displaystyle \mathbf{B}(x,y) = \int_0^1 t^{x-1}(1-t)^{y-1}\mbox{d}t\f$
//!     2.  if x or y is complex the value \f$\displaystyle  \mathbf{B}(x,y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$ is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/beta.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_beta beta = {};
}
