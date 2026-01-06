//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/asin.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct asinpi_t : eve::elementwise_callable<asinpi_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
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
      return  KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(asinpi_t, asinpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asinpi
//!   @brief Computes the arc sine of the argument in \f$\pi\f$ multiples.
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
//!     template<concepts::cayley_dickson_like Z> constexpr complexify_t<Z> asinpi(Z z) noexcept;
//!
//!     // semantic modifyers
//!     template<concepts::real Z> constexpr complexify_t<Z> asinpi[real_only](Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   - A real typed input z is treated as if `complex(z)` was entered unless the option real_only is used
//!     in which case the parameter must be a floating value, the real part of the result will the same as an eve::asinpi
//!     implying a Nan result if the result is not real.
//!   - returns `radinpi(asin(z))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asinpi.cpp}
//======================================================================================================================
  inline constexpr auto asinpi = eve::functor<asinpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asinpi_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    return radinpi(kyosu::asin[o](z));
  }
}
