//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_mulmi: eve::elementwise
  {
    using callable_tag_type = callable_mulmi;

    KYOSU_DEFERS_CALLABLE(mulmi_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return complex(T(0), -v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_mulmi(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var mulmi
//!   @brief Computes the value of the parameter multiplied by i on the left side.
//!   For real complex and quaternion the computation is an optimization over the call to * operator.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto  mulmi(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto  mulmi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * Returns -i(as(z))*z; If z is floating point a complex is returned.
//!       In the other cases the returned value as the same type as the input.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/mulmi.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_mulmi mulmi = {};
}
