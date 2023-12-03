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
  struct callable_cyl_bessel_yn: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_yn;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_yn_);

    template<eve::ordered_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v) noexcept { return eve::cyl_bessel_yn(n, v); }


    template<eve::integral_scalar_value N, eve::floating_ordered_value T, typename R>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v, R& ys) noexcept
    {
      auto fn = callable_cyl_bessel_yn{};
      return fn(n, v, ys);
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
    eve::unsupported_call<callable_cyl_bessel_yn(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_yn
//!   @brief Computes the modified Bessel functions of the second kind,
//!   \f$ Y_n(x)=\lim_{\alpha\to n}{{\frac {J_{\alpha  }(x)\cos(\alpha\pi)-J_{-\alpha }(x)}{\sin(\alpha\pi)}}}\f$,
//!   extended to the complex plane and cayley_dickson algebras.
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
//!      template<kyosu::concepts::cayley_dickson T>                                constexpr auto cyl_bessel_yn(int n, T z) noexcept;
//!      template<eve::floating_ordered_value N, eve::floating_ordered_value T>     constexpr T    cyl_bessel_yn(N n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$Y_n(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_yn.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_yn cyl_bessel_yn = {};
}
