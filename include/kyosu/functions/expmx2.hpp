//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/exp.hpp>
#include <kyosu/functions/sqr.hpp>

namespace kyosu
{
  template<typename Options> struct expmx2_t : eve::elementwise_callable<expmx2_t, Options, raw_option, pedantic_option, real_only_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(expmx2_t, expmx2_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var expmx2
  //!   @brief Computes the exponential of the opposite of the squared argument.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T expmx2(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns `exp(-z*z)`.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/expmx2.cpp}
  //======================================================================================================================
  inline constexpr auto expmx2 = eve::functor<expmx2_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto expmx2_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr (O::contains(radpi))
      return kyosu::exp[o.drop(radpi)](-sqr(eve::pi(eve::as_element_type_t<Z>())*z));
    else
       return kyosu::exp[o](-sqr(z));
  }
}
