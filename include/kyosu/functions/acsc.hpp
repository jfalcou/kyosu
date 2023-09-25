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
#include <kyosu/functions/to_complex.hpp>

namespace kyosu::tags
{
  struct callable_acsc : eve::elementwise
  {
    using callable_tag_type = callable_acsc;

    KYOSU_DEFERS_CALLABLE(acsc_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept {
      auto fn =  callable_acsc{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_acsc(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acsc
//!   @brief Computes the arccosecant of the argument.
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
//!      template<eve::ordered_value T>              constexpr auto acsc(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acsc(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if complex(z) was entered.
//!
//!   2. Returns elementwise \f$\mathop{\mathrm{asin}}(1/z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acsc.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_acsc acsc = {};
}
