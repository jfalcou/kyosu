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
  struct callable_cyl_bessel_kn: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_kn;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_kn_);

    template<eve::ordered_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v) noexcept { return eve::cyl_bessel_kn(n, v); }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_kn(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_kn
//!   @brief Computes the modified Bessel functions of the second kind,
//!   \f$ K_{n}(x)=\lim_{\alpha\to n}{\frac {\pi }{2}}{\frac {I_{-\alpha  }(x)-I_{\alpha }(x)}{\sin \alpha \pi }}\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_kn(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_bessel_kn(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$K_n(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_kn.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_kn cyl_bessel_kn = {};
}
