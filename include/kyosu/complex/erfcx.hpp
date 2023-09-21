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
  struct callable_erfcx : eve::elementwise
  {
    using callable_tag_type = callable_erfcx;

    KYOSU_DEFERS_CALLABLE(erfcx_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      return eve::erfcx(v);
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_erfcx(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var erfcx
//!   @brief Computes the normalized complementary error function
//!   \f$ \displaystyle \mbox{erfcx}(x) = e^{x^2} \mbox{erfc}(x)\f$.
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
//!      template<eve::ordered_value T>       constexpr auto erfcx(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T> constexpr auto erfcx(T z) noexcept;  //2
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
//!   2. The value of the normalized complementary error function is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/erfcx.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_erfcx erfcx = {};
}
