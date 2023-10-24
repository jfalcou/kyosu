//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_erf : eve::elementwise
  {
    using callable_tag_type = callable_erf;

    KYOSU_DEFERS_CALLABLE(erf_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      return eve::erf(v);
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_erf(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var erf
//!   @brief Computes the error function: \f$ \displaystyle
//!   \mbox{erf}(x)=\frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$ or
//!   its extension to complex and general cayley-dickson values
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
//!   {  template<eve::floating_ordered_value T>     constexpr T erf(T z) noexcept;
//!      template<kyosu::concepts::cayley_dickson T> constexpr T erf(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//! **Return value**
//!
//!   * The value of the error function is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/erf.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_erf erf = {};
}
