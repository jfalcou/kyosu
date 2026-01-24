//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/asin.hpp>
#include <kyosu/functions/rec.hpp>

namespace kyosu
{
  template<typename Options>
  struct acsc_t : eve::strict_elementwise_callable<acsc_t, Options, real_only_option>
  {

    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr  complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr  eve::as_wide_as_t<complexify_if_t<Options, Z>, K>
    operator()(Z const& z, K const & k) const noexcept
    {
     return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(acsc_t, acsc_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acsc
//!   @brief Computes the arccosecant of the argument.
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
//!     constexpr auto acsc(cayley_dickson_like z) noexcept;
//!     constexpr auto auto acsc(Z z, eve::value k) noexcept;
//!
//!     // semantic modifyers
//!     template<concepts::real Z> constexpr Z acsc[real_only](Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!   - A real typed input z is treated as if `complex(z)` was entered, unless the option real_only is used
//!     in which case the parameter must be a floating_value and the result will the same as a call to `eve::acsc`,
//!     implying a `Nan` result if the result is not real.
//!   - For complex input, returns elementwise `acos(rec(z))`.
//!   - for two parameters returns the kth branch of \f$\acsc\f$. If k is not a flint it is truncated before use.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Cosecant](https://mathworld.wolfram.com/InverseCosecant.html)
//!   *  [Wikipedia: Inverse trigonometric functions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
//!   *  [DLMF: Inverse trigonometric functions](https://dlmf.nist.gov/4.23)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/acsc.cpp}
//======================================================================================================================
  inline constexpr auto acsc = eve::functor<acsc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acsc_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    return  kyosu::asin[o](kyosu::rec(z));
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acsc_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  requires(!O::contains(real_only))
  {
    using e_t =  eve::element_type_t<decltype(real(z))>;
    auto kk = eve::convert(eve::trunc(k), eve::as<e_t>());
    return kyosu::acsc[o](z)+eve::two_pi(eve::as(kk))*kk;
  }

  template<concepts::real Z, eve::value ...K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acsc_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), acsc(z, k...));
  }
}
