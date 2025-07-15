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
#include <kyosu/functions/asec.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct asecpi_t : eve::elementwise_callable<asecpi_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(asecpi_t, asecpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asecpi
//!   @brief Computes the arc secant of the argument in \f$\pi\f$ multiples.
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
//!     template<concepts::cayley_dickson_like Z> constexpr complexify_t<Z> asecpi(Z z) noexcept;
//!
//!     // semantic modifyers
//!     template<concepts::real Z> constexpr complexify_t<Z> asecpi[real_only](Z z) noexcept;
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
//!     in which case the parameter must be a floating_value,  the real part of the result will the same as an eve::asecpi
//!     implying a Nan result if the result is not real.
//!   - For general cayley_dickson input, returns `radinpi(asec(z))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asecpi.cpp}
//======================================================================================================================
  inline constexpr auto asecpi = eve::functor<asecpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asecpi_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    return radinpi(kyosu::asec[o](z));
  }
}
