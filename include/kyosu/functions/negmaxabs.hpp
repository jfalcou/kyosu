//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/maxabs.hpp>

namespace kyosu
{
  template<typename Options>
  struct negmaxabs_t : eve::strict_elementwise_callable<negmaxabs_t, Options, eve::numeric_option, eve::pedantic_option>
  {
    template<typename Z0, typename ...Zs>
    requires(concepts::cayley_dickson<Z0> || (concepts::cayley_dickson<Zs>|| ...))
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0  const & z0, Zs const & ... zs) const noexcept
    -> decltype(eve::negmaxabs(real(z0), real(zs)...))
    {  return eve::minus(kyosu::maxabs[this->options()](z0, zs...)); }

    template<concepts::real V0, concepts::real... Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, Vs... vs) const noexcept
    -> decltype( eve::negmaxabs(v0, vs...))
    { return eve::negmaxabs[this->options()](v0,vs...); }

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
//!
//!  @godbolt{doc/negmaxabs.cpp}
//======================================================================================================================
  inline constexpr auto negmaxabs = eve::functor<negmaxabs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
