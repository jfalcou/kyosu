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
  struct callable_sph_bessel_ikn: eve::elementwise
  {
    using callable_tag_type = callable_sph_bessel_ikn;

    KYOSU_DEFERS_CALLABLE(sph_bessel_ikn_);

    template<eve::integral_scalar_value N, eve::floating_ordered_value T, typename R1, typename R2>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v, R1& i1s, R2& ks) noexcept
    //    requires(concepts::complex<decltype(js[0])> && concepts::complex<decltype(ys[0])>)
    {
      auto fn = callable_sph_bessel_ikn{};
      return fn(n, complex(v), i1s, ks);
    }

    template<typename N, typename T, typename R1, typename R2>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1, R1& output1, R2& output2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, output1, output2))
    {
      return eve::tag_invoke(*this, target0, target1, output1, output2);
    }

    template<typename... T>
    eve::unsupported_call<callable_sph_bessel_ikn(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_ikn
//!   @brief Computes the spherical Bessel functions i1 and k for integrals orders up to n
//!   @code
//!   #include <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!      template<eve::integral_scalar_value N, eve::floating_ordered_value T, complexRange R>
//!      constexpr auto sph_bessel_ikn(N n, T z, R& js,  R& ys) noexcept;
//!
//!      template<eve::integral_scalar_value N, conceots::kyosu::complex Z, complexRange R>
//!      constexpr T    sph_bessel_ikn(N n, Z z, R& js,  R& ys) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar positive integral order of the function.
//!     * `z`: Value to process.
//!     * `js: range able to contain n+1 complex values (of type complex_t<T> or Z respectively)
//!     * `ys: range able to contain n+1 complex values (of type complex_t<T> or Z respectively)
//!
//!   **Return value**
//!
//!     * returns the kumi pair \f$\{i1_n(z), k_n(z)\}f$.
//!
//!   *Ouput values
//!
//!     * on output js contains the values of   \f$((i1_{0+i})_{i = 0\cdot n}\f$
//!     * on output ys contains the values of   \f$((k_{0+i})_{i = 0\cdot n}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_ikn.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sph_bessel_ikn sph_bessel_ikn = {};
}
