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
  struct callable_to_quaternion
  {
    using callable_tag_type = callable_to_quaternion;

    KYOSU_DEFERS_CALLABLE(to_quaternion_);

    template<typename... T>
    KYOSU_FORCEINLINE auto operator()(T... target) const noexcept -> decltype(eve::tag_invoke(*this, target...))
    {
      return eve::tag_invoke(*this, target...);
    }

    template<typename... T>
    eve::unsupported_call<callable_to_quaternion(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var to_quaternion
//!   @brief Constructs a kyosu::quaternion
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
//!      template<eve::ordered_value T> constexpr auto to_quaternion(T r)            noexcept;
//!      template<eve::ordered_value T> constexpr auto to_quaternion(T r, T i)       noexcept;

//!      template<kyosu::concepts::cayley_dickson T> constexpr T to_quaternion(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`       : Quaternion value.
//!     * `r`, `i`  : Real and imaginary part sued to construct a @ref kyosu::quaternion..
//!
//!   **Return value**
//!
//!     Returns a @ref kyosu::quaternion constructed from its arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/to_quaternion.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_to_quaternion to_quaternion = {};
}

namespace kyosu::_
{
  template<eve::floating_value T>
  constexpr auto to_quaternion_(EVE_EXPECTS(eve::cpu_), T r)         noexcept  { return as_quaternion_t<T>(r, 0, 0, 0); }

  template<eve::floating_value T0, eve::floating_value T1>
  constexpr auto to_quaternion_(EVE_EXPECTS(eve::cpu_), T0 r, T1 i)  noexcept -> as_quaternion_t<decltype(eve::add(r, i))>
  {
    return as_quaternion_t<decltype(eve::add(r, i))>{r, i, 0, 0};
  }

  template<eve::floating_value T0, eve::floating_value T1, eve::floating_value T2, eve::floating_value T3>
  constexpr auto to_quaternion_(EVE_EXPECTS(eve::cpu_), T0 r, T1 i, T2 j, T3 k)  noexcept -> as_quaternion_t<decltype(eve::add(r, i, j, k))>
  {
    return as_quaternion_t<decltype(eve::add(r, i, j, k))>{r, i, j, k};
  }

  template<concepts::complex T0>
  constexpr auto to_quaternion_(EVE_EXPECTS(eve::cpu_), T0 const & c0)  noexcept
  {
    return to_quaternion(get<0>(c0), get<1>(c0));
  }

  template<concepts::complex T0,concepts::complex T1>
  constexpr auto to_quaternion_(EVE_EXPECTS(eve::cpu_), T0 const & c0, T1 const & c1)  noexcept
  {
    return to_quaternion(get<0>(c0), get<1>(c0),get<0>(c1), get<1>(c1));
  }

  template<concepts::quaternion T>
  constexpr auto to_quaternion_(EVE_EXPECTS(eve::cpu_), T const& v)  noexcept
  {
    return v;
  }

}
