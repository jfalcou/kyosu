//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/types/complex.hpp>

namespace kyosu::tags
{
  struct callable_k : eve::elementwise
  {
    using callable_tag_type = callable_k;

    KYOSU_DEFERS_CALLABLE(k_);

    template<eve::value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, as<T> const& ) noexcept
    requires(concepts::cayley_dickson<T> || eve::floating_ordered_value<T>)
    {
      using u_t = eve::underlying_type_t<T>;
      return kyosu::quaternion(u_t(0),u_t(0), u_t(0), u_t(1)); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_abs(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var i
//!   @brief Computes the complex number k i.e. quaternion(0, 0, 0, 1) in the chosen type.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr as_complex_t<underlying_type_t<T>>  k(as<T> z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr �s_complex_t<underlying_type_t<T>>  k(as<T> z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * always returns a quaternion scalar value k such that all parts are null exceptthe k part whose value is one.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/i.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_k k = {};
}
