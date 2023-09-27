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
  struct callable_acoth : eve::elementwise
  {
    using callable_tag_type = callable_acoth;

    KYOSU_DEFERS_CALLABLE(acoth_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_acoth{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_acoth(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acoth
//!   @brief Computes the inverse hyperbolic cotangent of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto acoth(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T>        constexpr auto acoth(T z) noexcept;  //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acoth(T z) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if [kyosu::complex](@ref kyosu::complex)(z) was entered.
//!
//!   2. Returns the complex inverse hyperbolic cotangent of z, computed as \f$\mathop{\mathrm{atanh}}(1/z)\f$.
//!
//!   3. Returns \f$(\log(z+1)-\log(z-1))/2 \f$.
//!
///!  @groupheader{Example}
//!
//!  @godbolt{doc/acoth.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_acoth acoth = {};
}
