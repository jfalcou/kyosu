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
#include <kyosu/functions/sqr_abs.hpp>

namespace kyosu
{
  template<typename Options>
  struct minmag_t : eve::strict_elementwise_callable<minmag_t, Options>
  {
     template<typename C0, typename C1, typename ...Cs>
    requires(concepts::cayley_dickson<C0> || concepts::cayley_dickson<C1> || (concepts::cayley_dickson<Cs> || ...))
      KYOSU_FORCEINLINE constexpr auto  operator()(C0 const& c0, C1 const& c1, Cs const & ...cs) const noexcept -> kyosu::as_cayley_dickson_t<C0, C1, Cs...>
    {
      if constexpr(sizeof...(cs) == 0)
      {
        auto ac0 = kyosu::sqr_abs(c0);
        auto ac1 = kyosu::sqr_abs(c1);
        auto tmp = kyosu::if_else(eve::is_not_greater_equal(ac1, ac0), c1, c0);
        return kyosu::if_else(eve::is_not_greater_equal(ac0, ac1), c0, tmp);
      }
      else
      {
        using r_t = kyosu::as_cayley_dickson_t<C0, C1, Cs...>;
        r_t that(minmag(c0, c1));
        ((that = minmag(that, cs)), ...);
        return that;
      }
    }

    template<concepts::real V0, concepts::real ...Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, Vs... vs) const noexcept -> decltype(eve::minmag(v0,vs...))
    { return eve::minmag(v0,vs...); }

    KYOSU_CALLABLE_OBJECT(minmag_t, minmag_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var minmag
//!   @brief Callable object computing the minmag operation.
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
//!      template<typename ... Ts> auto minmag(Ts ... zi ) const noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns elementwise  the value which has the minimum of the absolute values between the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/minmag.cpp}
//======================================================================================================================
  inline constexpr auto minmag = eve::functor<minmag_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
