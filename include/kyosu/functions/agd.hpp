//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/tan.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options> struct agd_t : eve::strict_elementwise_callable<agd_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(agd_t, agd_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var agd
  //!   @brief Computes the principal branch inverse gudermanian of the argument.
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
  //!     constexpr auto agd(cayley_dickson_like z) noexcept;
  //!
  //!     // semantic modifyers
  //!     constexpr auto agd[real_only](Real z)      noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     - A real typed input z is treated as if `complex(z)` was entered, unless the option real_only is used
  //!       in which case the parameter must be a floating_value and the result will the same as a call to `eve::agd`,
  //!     - For complex input, returns \f$\log(\tan(z/2 +\pi/4))\f$.
  //!
  //!    @note `agd` has branch cut discontinuities in \f$[\pi/2, 3\pi/2] + 2\pi n\f$ in the complex
  //!      plane for integer  \f$n\f$. Morover,  with `real_only` option the used formula is
  //!      \f$2*\mathbb{atan}(\tanh(z/2))\f$
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Inverse Gudermannian](https://mathworld.wolfram.com/Gudermannian.html)
  //!   *  [Wikipedia: Gudermannian function](https://en.wikipedia.org/wiki/Gudermannian_function)
  //!   *  [Wikipedia: Inverse Gudermannian function](https://en.wikipedia.org/wiki/InverseGudermannian_function)
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/agd.cpp}
  //======================================================================================================================
  inline constexpr auto agd = eve::functor<agd_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto agd_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (O::contains(real_only) && concepts::real<Z>) return eve::agd(z);
    else if constexpr (concepts::real<Z>) return kyosu::agd(complex(z));
    else if constexpr (concepts::complex<Z>)
      return kyosu::log(kyosu::tan(z * kyosu::half(as(z)) + kyosu::pio_4(as(z))));
    else return kyosu::_::cayley_extend(kyosu::agd, z);
  }

  template<concepts::real Z, eve::value... K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto agd_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), agd(z, k...));
  }
}
