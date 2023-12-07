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
  struct callable_cyl_bessel_y: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_y;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_y_);

    template<eve::floating_scalar_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N nu, T const& v) noexcept
    {
      auto fnu = callable_cyl_bessel_y{};
      return fnu(nu, complex(v));
    }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_y(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_y
//!   @brief Computes the Bessel functions of the first kind,
//!   \f$ J_{\nu}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+\nu +1)}}
//!   {\left({x \over 2}\right)}^{2p+\nu }\f$
//!   extended to the complex plane and cayley_dickson values.
//!
//!   It is the solution of \f$ x^{2}y''+xy'+(x^2-\nu^2)y=0\f$ for which
//!   \f$ y(0) = 0\f$ if \f$\nu \ne 0\f$ else \f$1\f$.
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
//!      template<eve::floating_ordered_value, kyosu::concepts::cayley_dickson T>
//!      constexpr auto cyl_bessel_y(N nu, T z) noexcept;
//!
//!      template<eve::floating_ordered_value, eve::floating_ordered_value T>
//!      constexpr T    cyl_bessel_y(N n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `nu`: order of the function.
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$J_\nu(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_y.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_y cyl_bessel_y = {};
}
