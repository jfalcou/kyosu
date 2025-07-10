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
#include <kyosu/functions/acsc.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct acscpi_t : eve::elementwise_callable<acscpi_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(acscpi_t, acscpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acscpi
//!   @brief Computes the arc cosecant of the argument in \f$\pi\f$ multiples.
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
//!     template<concepts::cayley_dickson_like Z> constexpr complexify_t<Z> acscpi(Z z) noexcept;
//!
//!     // semantic modifyers
//!     template<concepts::real Z> constexpr complexify_t<Z> acscpi[real_only](Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   - A real input z is treated as if `complex(z)` was enteredunless the option real_only is used
//!     in which case the parameter must be a floating_value,  the real part of the result will the same as an eve::acscpi
//!     implying a Nan result if the result is not real.
//!   - Returns `radinpi(acsc(z))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acscpi.cpp}
//======================================================================================================================
  inline constexpr auto acscpi = eve::functor<acscpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acscpi_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    return radinpi(kyosu::acsc[o](z));
  }
}
