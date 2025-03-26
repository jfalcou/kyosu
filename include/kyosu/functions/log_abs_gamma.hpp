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
#include <kyosu/functions/log_abs.hpp>
#include <kyosu/functions/tgamma.hpp>

namespace kyosu
{
  template<typename Options>
  struct log_abs_gamma_t : eve::elementwise_callable<log_abs_gamma_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z const& z) const noexcept
    {
      return  KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(log_abs_gamma_t, log_abs_gamma_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log_abs_gamma
//!   @brief Computes the log of the modulus of the \f$\Gamma\f$ function of the parameter.
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
//!     constexpr auto  log_abs_gamma(auto z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns \f$\log(|\Gamma(z)|)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log_abs_gamma.cpp}
//======================================================================================================================
  inline constexpr auto log_abs_gamma = eve::functor<log_abs_gamma_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log_abs_gamma_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::real<Z>)
      return eve::log_abs(eve::tgamma(z));
    else
      return kyosu::log_abs(kyosu::tgamma(z));
  }
}
