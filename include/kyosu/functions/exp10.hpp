//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options> struct exp10_t : eve::elementwise_callable<exp10_t, Options, radpi_option, rad_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(exp10_t, exp10_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var exp10
  //!   @brief Computes the base 10 exponential of the argument.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T exp10(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns 10 to the argument. The call is semantically equivalent to \f$e^{\log(10)z}\f$
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/exp10.cpp}
  //======================================================================================================================
  inline constexpr auto exp10 = eve::functor<exp10_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto exp10_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr (concepts::real<Z>) return eve::exp10(z);
    else return kyosu::exp[o](z * kyosu::log_10(eve::as_element<Z>()));
  }
}
