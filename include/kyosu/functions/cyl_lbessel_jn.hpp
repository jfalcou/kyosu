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
  struct callable_cyl_lbessel_jn: eve::elementwise
  {
    using callable_tag_type = callable_cyl_lbessel_jn;

    KYOSU_DEFERS_CALLABLE(cyl_lbessel_jn_);

    template<eve::ordered_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v) noexcept
    {
      callable_cyl_lbessel_jn fn{};
      return fn(n, complex(v));

    }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_lbessel_jn(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @brief Computes the logarithm of the Bessel functions of the first kind,
//!   \f$ J_{n}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+n +1)}}
//!   {\left({x \over 2}\right)}^{2p+n }\f$.
//!
//!   \f$ J_{n}\f$ is the solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_lbessel_jn(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_lbessel_jn(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * return the cylindrical \f$J_n(z)\f$.  If T is a floating point value (real), a complex value is returned.
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_lbessel_jn.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_lbessel_jn cyl_lbessel_jn = {};
}
