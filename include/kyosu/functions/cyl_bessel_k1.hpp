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
  struct callable_cyl_bessel_k1: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_k1;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_k1_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::cyl_bessel_k1(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_k1(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_k1
//!   @brief Computes  the Bessel function of the second kind,
//!   \f$ K_1(x)\lim_{\alpha\to 1}{\frac {\pi }{2}}{\frac {I_{-\alpha }(x)-I_{\alpha }(x)}{\sin \alpha \pi }}\f$ extended to the complex plane and cayley_dickson values.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_k1(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto cyl_bessel_k1(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$K_1(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_k1.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_k1 cyl_bessel_k1 = {};
}
