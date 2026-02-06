//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/atan.hpp>
#include <kyosu/functions/rec.hpp>

namespace kyosu
{
  template<typename Options> struct acot_t : eve::strict_elementwise_callable<acot_t, Options, real_only_option>
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

    KYOSU_CALLABLE_OBJECT(acot_t, acot_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var acot
  //!   @brief Computes the arc cotangent of the argument.
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
  //!     constexpr auto acot(cayley_dickson_like z)                  noexcept;
  //!     constexpr auto acot(cayley_dickson_like z, eve::value k)    noexcept;
  //!
  //!     // semantic modifyers
  //!     constexpr auto acot[real_only](Real z)                      noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //! **Return value**
  //!
  //!    - A real typed input `z` is treated as if `complex(z)` was entered, unless the option real_only is used
  //!      in which case the parameter must be a floating_value and the result will the same as a call to `eve::acot`,
  //!    - For complex input, returns elementwise the complex principal value
  //!        of the arc cotangent of the input as the arc tangent of the inverse of the input.
  //!    - For other general cayley_dickson input, returns \f$I_z \mathrm{acoth}(z I_z)\f$ where \f$I_z =
  //!    \frac{\underline{z}}{|\underline{z}|}\f$ and
  //!         \f$\underline{z}\f$ is the [pure](@ref pure)  part of \f$z\f$.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Inverse Cotangent](https://mathworld.wolfram.com/InverseCotangent.html)
  //!   *  [DLMF: Inverse trigonometric functions](https://dlmf.nist.gov/4.23)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/acot.cpp}
  //======================================================================================================================
  inline constexpr auto acot = eve::functor<acot_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acot_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    return kyosu::atan[o](kyosu::rec(z));
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acot_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  requires(!O::contains(real_only))
  {
    using e_t = eve::element_type_t<decltype(real(z))>;
    auto kk = eve::convert(eve::trunc(k), eve::as<e_t>());
    return kyosu::acot[o](z) + eve::two_pi(eve::as(kk)) * kk;
  }

  template<concepts::real Z, eve::value... K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acot_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), acot(z, k...));
  }
}
