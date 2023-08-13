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
  struct callable_conj : eve::elementwise
  {
    using callable_tag_type = callable_conj;

    KYOSU_DEFERS_CALLABLE(conj_);

    template<typename T>
    EVE_FORCEINLINE auto operator()(T target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_conj(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var conj
//!   @brief Computes the conjugate value.
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
//!      template<kyosu::concepts::cayley_dickinson T> constexpr T conj(T z) noexcept;
//!      template<eve::ordered_value T>               constexpr T conj(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to conjugate.
//!
//!   **Return value**
//!
//!     Returns the conjugate of its argument. i.e. the value with the same real part
//!     and the opposite pure part.
//!
//!     For real inputs the call reduces to identity.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/conj.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_conj conj = {};
}

namespace kyosu::_
{
  template<eve::ordered_value T> constexpr auto conj_(EVE_EXPECTS(eve::cpu_), T v) noexcept
  {
    return v;
  }

  template<concepts::cayley_dickinson T> constexpr auto conj_(EVE_EXPECTS(eve::cpu_), T const& v) noexcept
  {
    return T{kumi::map_index([]<typename I>(I, auto m) { if constexpr(I::value>0) return -m; else return m;}, v)};
  }
}
