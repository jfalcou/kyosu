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
  template<typename Options> struct exp2_t : eve::elementwise_callable<exp2_t, Options>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(exp2_t, exp2_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var exp2
  //!   @brief Computes the base 2 exponential of the argument.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T exp2(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns 2 to the argument. The call is semantically equivalent to \f$e^{\log(2)z}\f$
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/exp2.cpp}
  //======================================================================================================================
  inline constexpr auto exp2 = eve::functor<exp2_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto exp2_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (concepts::real<Z>) return eve::exp2(z);
    else return kyosu::exp(z * kyosu::log_2(eve::as_element<Z>()));
  }
}
