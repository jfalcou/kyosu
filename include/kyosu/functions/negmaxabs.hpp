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
#include <kyosu/functions/maxabs.hpp>

namespace kyosu
{
  template<typename Options>
  struct negmaxabs_t : eve::strict_elementwise_callable<negmaxabs_t, Options, eve::numeric_option, eve::pedantic_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like ...Zs>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Zs... zs) const noexcept -> decltype(eve::maxabs(real(z0), real(zs)...))
    {
      return KYOSU_CALL(z0, zs...);
    }

    KYOSU_CALLABLE_OBJECT(negmaxabs_t, negmaxabs_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var negmaxabs
//!   @brief Callable object computing the negmaxabs operation.
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
//!      template<typename ... Ts> auto negmaxabs(Ts ... zi ) const noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns elementwise  the negated maximum of the absolute values of the parameters.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/negmaxabs.cpp}
//======================================================================================================================
  inline constexpr auto negmaxabs = eve::functor<negmaxabs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, typename Z0, typename ...Zs>
  KYOSU_FORCEINLINE constexpr
  auto negmaxabs_(KYOSU_DELAY(), O const& o, Z0 z0, Zs... zs) noexcept
  {
    if constexpr(concepts::real<Z0> && (... && concepts::real<Zs>))
      return eve::negmaxabs[o](z0,zs...);
    else
      return eve::minus(kyosu::maxabs[o](z0, zs...));
  }
}
