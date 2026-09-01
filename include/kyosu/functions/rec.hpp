//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/if_else.hpp>
#include <kyosu/functions/is_infinite.hpp>
#include <kyosu/functions/sqr_abs.hpp>
#include <kyosu/functions/conj.hpp>
#include <kyosu/functions/is_not_real.hpp>

namespace kyosu
{
  template<typename Options> struct rec_t : eve::elementwise_callable<rec_t, Options, raw_option, pedantic_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(rec_t, rec_);
  };

  //======================================================================================================================
  //! @defgroup rec kyosu::rec
  //! @ingroup agnostic
  //! @brief Computes the inverse of the argument.
  //! @{
  //!   @var rec
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
  //!      // Regular Calls
  //!      template<kyosu::concepts::cayley_dickson T> constexpr T rec(T z) noexcept;
  //!      template<eve::floating_ordered_value T>     constexpr T rec(T z) noexcept;
  //!
  //!      // Lanes masking
  //!      constexpr auto rec[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 4
  //!      constexpr auto rec[logical_value auto m](/*any of the above overloads*/)     noexcept; // 4
  //!
  //!      // Semantic Calls
  //!      template<kyosu::concepts::cayley_dickson T> constexpr T rec[pedantic](T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     1. Returns the inverse of the argument.
  //!     2. std::complex like behaviour with infinite or na entries entries
  //!
  //!     @note the regular inverse call applied to \f$\pm 0\f$ does not follow
  //!      std::complex standard: the imaginary part is 0.
  //!      Use pedantic if you think that an imaginary nan is a better result.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/rec.cpp}
  //======================================================================================================================
  inline constexpr auto rec = eve::functor<rec_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto rec_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (concepts::real<Z>) return eve::rec(z);
    else if constexpr (O::contains(pedantic))
    {
      auto zz = if_else(kyosu::is_not_real(z), conj(z),
                        Z(real(z), eve::copysign(eve::zero(eve::as(kyosu::real(z))), kyosu::real(z))));
      return if_else(is_nez(z), zz / sqr_abs(z),
                     Z(eve::copysign(eve::inf(eve::as(kyosu::real(z))), kyosu::real(z)), eve::nan(eve::as(real(z)))));
    }
    else
    {
      return if_else(kyosu::is_real(z),
                     Z(eve::rec(real(z)), eve::copysign(eve::zero(eve::as(kyosu::real(z))), kyosu::real(z))),
                     if_else(is_infinite(z), eve::zero, conj(z) / sqr_abs(z)));
    }
  }
}
