//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/atanh.hpp>
#include <kyosu/details/decorators.hpp>

namespace kyosu
{
  template<typename Options> struct atan_t : eve::strict_elementwise_callable<atan_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<complexify_if_t<Options, Z>, K> operator()(Z const& z,
                                                                                             K const& k) const noexcept
    {
      return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(atan_t, atan_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var atan
  //!   @brief Computes the arctangent of the argument.
  //!
  //!   @groupheader{Header file}
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
  //!     //  regular call
  //!     constexpr auto atan(cayley_dickson_like z)                noexcept;
  //!     constexpr auto atan(cayley_dickson_like z, eve::value k)  noexcept;
  //!
  //!     // semantic modifyers
  //!      constexpr Z atan[real_only](Real z)                      noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //! **Return value**
  //!
  //!    - A real typed input `z` is treated as if `complex(z)` was entered unless the option real_only is used
  //!      in which case the parameter must be a floating_value and the result will the same as a call to `eve::acos`,
  //!    - For complex input, returns the elementwise the complex principal value
  //!      of the arc tangent of the input in the range of a strip unbounded along the imaginary axis
  //!      and in the interval \f$[-\pi/2, \pi/2]\f$ along the real axis.
  //!      Special cases are handled as if the operation was implemented by \f$-i\; \mathrm{atanh}(z\; i)\f$.
  //!
  //!    - For generated cayley_dickson input, returns \f$ -I_z \mathrm{atanh}(z I_z)\f$ where \f$I_z =
  //!    \frac{\underline{z}}{|\underline{z}|}\f$ and
  //!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference: atan](https://en.cppreference.com/w/cpp/numeric/complex/atan)
  //!   *  [Wolfram MathWorld: Inverse Tangent](https://mathworld.wolfram.com/InverseTangent.html)
  //!   *  [Wikipedia: Inverse trigonometric functions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
  //!   *  [DLMF: Inverse trigonometric functions](https://dlmf.nist.gov/4.23)
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/atan.cpp}
  //======================================================================================================================
  inline constexpr auto atan = eve::functor<atan_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<concepts::cayley_dickson_like Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto atan_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (O::contains(real_only) && concepts::real<Z>) return eve::atan(z);
    else if constexpr (concepts::real<Z>) return kyosu::atan(complex(z));
    else if constexpr (concepts::complex<Z>)
    {
      // C99 definition here; atan(z) = -i atanh(i*z):
      auto [r, i] = z;
      auto [r1, i1] = kyosu::atanh(complex(-i, r));
      return complex(i1, -r1);
    }
    else { return _::cayley_extend(kyosu::atan, z); }
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto atan_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  requires(!O::contains(real_only))
  {
    using e_t = eve::element_type_t<decltype(real(z))>;
    auto kk = eve::convert(eve::trunc(k), eve::as<e_t>());
    return kyosu::atan[o](z) + eve::two_pi(eve::as(kk)) * kk;
  }

  template<concepts::real Z, eve::value... K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto atan_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), atan(z, k...));
  }

}
