//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_log1p: eve::elementwise
  {
    using callable_tag_type = callable_log1p;

    KYOSU_DEFERS_CALLABLE(log1p_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_log1p{};
      return fn( kyosu::complex(v, T(0)));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_log1p(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log1p
//!   @brief Computes the natural logarithm of the argument plus 1.
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
//!      template<eve::floating_ordered_value T>     constexpr complex_t<T> log1p(T z) noexcept; //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr T log1p(T z) noexcept;            //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!   1.  a real typed input z is treated as if [kyosu::complex](@ref kyosu::complex)(z) was entered.\n
//!       For real and complex entries provision are made to get better precision near z = 0.
//!
//!   2.  returns [log](@ref kyosu::log)(1+z).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log1p.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_log1p log1p = {};
}
