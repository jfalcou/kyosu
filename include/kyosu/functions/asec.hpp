//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/acos.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct asec_t : eve::elementwise_callable<asec_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    requires(!Options::contains(real_only))
     {
      if constexpr(concepts::real<Z>)
        return (*this)(complex(z));
      else
        return  KYOSU_CALL(z);
    }

    template<concepts::real Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    requires(Options::contains(real_only))
    {
      auto r = eve::asec(z);
      return complex(r, eve::if_else(eve::is_nan(r), eve::nan, eve::zero(as(r))));
    }

    KYOSU_CALLABLE_OBJECT(asec_t, asec_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asec
//!   @brief Computes the arcsecant of the argument.
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
//!     template<concepts::cayley_dickson_like Z> constexpr complexify_t<Z> asec(Z z) noexcept;
//!
//!     // semantic modifyers
//!     template<concepts::real Z> constexpr complexify_t<Z> asec[real_only](Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   - A real typed input z is treated as if `complex(z)` was entered.
//!   - For complex input, returns elementwise `acos(rec(z))`.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Secant](https://mathworld.wolfram.com/InverseSecant.html)
//!   *  [Wikipedia: Inverse trigonometric functions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
//!   *  [DLMF: Inverse trigonometric functions](https://dlmf.nist.gov/4.23)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/asec.cpp}
//======================================================================================================================
  inline constexpr auto asec = eve::functor<asec_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asec_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    return  kyosu::acos[o](kyosu::rec(z));
  }
}
