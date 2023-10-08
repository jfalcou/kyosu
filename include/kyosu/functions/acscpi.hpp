//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_acscpi: eve::elementwise
  {
    using callable_tag_type = callable_acscpi;

    KYOSU_DEFERS_CALLABLE(acscpi_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_acscpi{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_acscpi(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acscpi
//!   @brief Computes the arc cosecant of the argume!nt in \f$\pi\f$ multiples.
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
//!      template<eve::floating_ordered_value T>     constexpr auto acscpi(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acscpi(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if [kyosu::complex](@ref kyosu::complex)(z) was entered.
//!
//!   2. Returns Returns kyosu::radinpi([kyosu::csc](@ref kyosu::acsc)(z))
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acscpi.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_acscpi acscpi = {};
}
