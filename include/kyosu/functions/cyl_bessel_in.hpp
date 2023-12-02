//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/bessel.hpp>

namespace kyosu::tags
{
  struct callable_cyl_bessel_in: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_in;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_in_);

    template<eve::ordered_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v) noexcept
    {
      return eve::cyl_bessel_in(n, v);
    }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_in(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_in
//!   @brief Computes the modified Bessel functions of the first kind \f$I_{n}(x)=i^{-n}J_{n }(ix)\f$,
//!   extended to the complex plane and cayley_dickson algebras.
//!
//!   It is the solution of \f$ x^{2}y''+xy'+(x^2+n^2)y=0\f$ for which
//!   \f$ y(0) = 0\f$ if \f$n \ne 0\f$ else \f$1\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_in(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_bessel_in(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$J_n(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_in.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_in cyl_bessel_in = {};
}
