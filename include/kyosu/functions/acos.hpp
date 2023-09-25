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
  struct callable_acos : eve::elementwise
  {
    using callable_tag_type = callable_acos;

    KYOSU_DEFERS_CALLABLE(acos_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept {
      auto fn =  callable_acos{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_acos(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acos
//!   @brief Computes the acosine of the argument.
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
//!      template<eve::ordered_value T>              constexpr auto acos(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T>        constexpr auto atan(T z) noexcept;  //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acos(T z) noexcept;  //3
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
//!   2. Returns elementwise the complex principal value
//!      of the arc cosine of the input.
//!      Branch cuts exist outside the interval \f$[-1, +1]\f$ along the real axis.
//!
//!      * for every z: eve::acos(eve::conj(z)) == eve::conj(std::acos(z))
//!      * If z is \f$\pm0\f$, the result is \f$\pi/2\f$
//!      * If z is \f$i NaN\f$, the result is \f$\pi/2+ i NaN\f$
//!      * If z is \f$x+i\infty\f$ (for any finite x), the result is \f$\pi/2-i\infty\f$
//!      * If z is \f$x+i NaN\f$ (for any nonzero finite x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$-\infty+i y\f$ (for any positive finite y), the result is \f$\pi-i\infty\f$
//!      * If z is \f$+\infty+i y\f$ (for any positive finite y), the result is \f$+0-i\infty\f$
//!      * If z is \f$-\infty+i +\infty\f$, the result is \f$3\pi/4-i\infty\f$
//!      * If z is \f$\infty+i +\infty\f$, the result is \f$\pi/4-i\infty\f$
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$NaN \pm i\infty\f$ (the sign
//!        of the imaginary part is unspecified)
//!      * If z is \f$NaN+i y\f$ (for any finite y), the result is \f$NaN+i NaN\f$
//!      * If z is \f$NaN+i\infty\f$, the result is \f$NaN-i\infty\f$
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!   3. Returns \f$I_z \mathrm{acosh}(z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the pure part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acos.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_acos acos = {};
}
