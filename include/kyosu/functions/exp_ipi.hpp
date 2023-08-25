//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_exp_ipi : eve::elementwise
  {
    using callable_tag_type = callable_exp_ipi;

    KYOSU_DEFERS_CALLABLE(exp_ipi_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      const auto ii = kyosu::to_complex(T(0), T(1))*pi(as<T>());
      return kyosu::exp(ii*v);
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_exp_ipi(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp_ipi
//!   @brief Computes the exponential of the argument times i.
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
//!      template<kyosu::concepts::cayley_dickson T> constexp_ipir T exp_ipi(T z) noexcept;
//!      template<eve::ordered_value T>              constexp_ipir T exp_ipi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns the `exp(i*z)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp_ipi.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_exp_ipi exp_ipi = {};
}