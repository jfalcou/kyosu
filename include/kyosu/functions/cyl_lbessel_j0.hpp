//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>


namespace kyosu::tags
{
  struct callable_cyl_lbessel_j0: eve::elementwise
  {
    using callable_tag_type = callable_cyl_lbessel_j0;

    KYOSU_DEFERS_CALLABLE(cyl_lbessel_j0_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_cyl_lbessel_j0{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_lbessel_j0(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_lbessel_j0
//!   @brief Computes  the logarithm of the bessel function of the first kind,
//!   \f$ J_0(x)=\frac1{\pi }\int _{0}^{\pi}\cos(x\sin \tau)
//!   \,\mathrm {d} \tau \f$ extended to the complex plane and cayley_dickson values.
//!
//!   In the real field, it is the solution of \f$ x^{2}y''+xy'+x^2y=0\f$ for which \f$ y(0) = 1\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_lbessel_j0(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_lbessel_j0(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * return \f$\log(J_0(z))\f$. If T is a floating point value (real), a complex value is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_lbessel_j0.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_lbessel_j0 cyl_lbessel_j0 = {};
}
