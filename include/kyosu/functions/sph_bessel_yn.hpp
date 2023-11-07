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
  struct callable_sph_bessel_yn: eve::elementwise
  {
    using callable_tag_type = callable_sph_bessel_yn;

    KYOSU_DEFERS_CALLABLE(sph_bessel_yn_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, int n, T const& v) noexcept { return eve::sph_bessel_yn(n, v); }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_sph_bessel_yn(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_yn
//!   @brief Computes the spherical Bessel functions of the first kind \f$y_{n}(x)\f$,
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_yn(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    sph_bessel_yn(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$y_n(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_yn.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sph_bessel_yn sph_bessel_yn = {};
}
