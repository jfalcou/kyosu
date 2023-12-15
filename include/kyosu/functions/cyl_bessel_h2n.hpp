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
  struct callable_cyl_bessel_h2n: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_h1n;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_h2n_);

    template<eve::ordered_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& z) noexcept
    {
      using e_t = eve::element_type_t<T>;
      return complex(cyl_bessel_jn(n, z), -cyl_bessel_yn(n, z));
    }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_h2n(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_h2n
//!   @brief Computes the Bessel/Hankel functions of the third kind ,
//!   \f$ H_n^{(2)} =  J_n(z)-iY_n(z)\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_h2n(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto cyl_bessel_h2n(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * return  \f$H_n^{(2)}(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h2n.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_h2n cyl_bessel_h2n = {};
}
