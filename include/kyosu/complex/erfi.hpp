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
  struct callable_erfi : eve::elementwise
  {
    using callable_tag_type = callable_erfi;

    KYOSU_DEFERS_CALLABLE(erfi_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto over = eve::sqr(v) > 720;
      auto r = eve::inf(eve::as(v))*eve::sign(v);
      r = eve::if_else(over,  r, -kyosu::imag(kyosu::erf(to_complex(eve::zero(eve::as(v)), -v))));
      return to_complex(r);
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const & target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_erfi(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var erfi
//!   Callable object computing The imaginary error function \f$ \displaystyle \mathrm{erfi}(z) = -i\mathrm{erf](iz)\f$
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
//!      template<eve::ordered_value T>       constexpr auto erfi(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T> constexpr auto erfi(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Vcomplex or real value to process.
//!
//! **Return value**
//!
//!   Returns the imaginary error function \f$ \displaystyle \mathrm{erfi}(z) = -i\mathrm{erf}(iz)\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/erfi.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_erfi erfi = {};
}
