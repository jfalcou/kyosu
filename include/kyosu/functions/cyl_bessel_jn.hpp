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
  struct callable_cyl_bessel_jn: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_jn;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_jn_);

    template<eve::integral_scalar_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v) noexcept
    {
      return eve::cyl_bessel_jn(n, v);
    }

    template<eve::integral_scalar_value N, eve::floating_ordered_value T, typename R>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v, R& js) noexcept
    {
      auto fn = callable_cyl_bessel_jn{};
      return fn(n, v, js);
    }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename N, typename T, typename R>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1, R & target2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, target2))
    {
      return eve::tag_invoke(*this, target0, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_jn(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_jn
//!   @brief Computes the Bessel functions of the first kind,
//!   \f$ J_{n}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+n +1)}}
//!   {\left({x \over 2}\right)}^{2p+n }\f$
//!   extended to the complex plane and cayley_dickson values.
//!
//!   It is the solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_jn(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_bessel_jn(int n, T z) noexcept;
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
//!  @godbolt{doc/cyl_bessel_jn.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_jn cyl_bessel_jn = {};
}
