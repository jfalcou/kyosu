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
  struct callable_jpart : eve::elementwise
  {
    using callable_tag_type = callable_jpart;

    KYOSU_DEFERS_CALLABLE(jpart_);

    template<typename T>
    EVE_FORCEINLINE auto operator()(T&& target) const noexcept -> decltype(eve::tag_invoke(*this, KYOSU_FWD(target)))
    {
      return eve::tag_invoke(*this, KYOSU_FWD(target));
    }

    template<typename... T>
    eve::unsupported_call<callable_jpart(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var jpart
//!   @brief Extracts the \f$j\f$  part of a value.
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
//!      template<kyosu::concepts::cayley_dickinson T> constexpr auto& jpart(T& z)        noexcept;
//!      template<kyosu::concepts::cayley_dickinson T> constexpr auto  jpart(T const& z)  noexcept;
//!      template<eve::ordered_value T>                constexpr T     jpart(T const& z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Original value.
//!
//!   **Return value**
//!
//!     Returns the \f$j\f$  part of its argument. For real and complex inputs, the call returns 0.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/jpart.cpp}
//======================================================================================================================
inline constexpr tags::callable_jpart jpart = {};

//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<eve::ordered_value T>
  EVE_FORCEINLINE constexpr auto  jpart_(EVE_EXPECTS(eve::cpu_), T const&) noexcept { return T{0}; }

  template<concepts::cayley_dickinson C>
  EVE_FORCEINLINE constexpr decltype(auto)  jpart_(EVE_EXPECTS(eve::cpu_), C&& c) noexcept
  {
    if constexpr(dimension_v<C> >= 4) return get<2>(EVE_FWD(c));
    else                              return eve::underlying_type_t<std::remove_cvref_t<C>>{0};
  }
}
