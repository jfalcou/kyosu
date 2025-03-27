//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/minabs.hpp>

namespace kyosu
{
  template<typename Options>
  struct negminabs_t : eve::strict_elementwise_callable<negminabs_t, Options,
                                                        eve::numeric_option, eve::pedantic_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like ...Zs>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Zs... zs) const noexcept -> decltype(eve::maxabs(real(z0), real(zs)...))
    {
      return KYOSU_CALL(z0, zs...);
    }

    KYOSU_CALLABLE_OBJECT(negminabs_t, negminabs_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var negminabs
//!   @brief Callable object computing the negminabs operation.
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
//!      template<typename ... Ts> auto negminabs(Ts ... zi ) const noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns elementwise  the negated minimum of the absolute values of the parameters.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/negminabs.cpp}
//======================================================================================================================
  inline constexpr auto negminabs = eve::functor<negminabs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, typename Z0, typename ...Zs>
  KYOSU_FORCEINLINE constexpr
  auto negminabs_(KYOSU_DELAY(), O const& o, Z0 z0, Zs... zs) noexcept
  {
    if constexpr(concepts::real<Z0> && (... && concepts::real<Zs>))
      return eve::negminabs[o](z0,zs...);
    else
      return eve::minus(kyosu::minabs[o](z0, zs...));
  }
}
