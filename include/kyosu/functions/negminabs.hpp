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
#include <kyosu/functions/minabs.hpp>

namespace kyosu
{
  template<typename Options>
  struct negminabs_t : eve::strict_elementwise_callable<negminabs_t, Options,
                                                        eve::numeric_option, eve::pedantic_option>
  {
    template<typename Z0, typename ...Zs>
    requires(concepts::cayley_dickson<Z0> || (concepts::cayley_dickson<Zs>|| ...))
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0  const & z0, Zs const & ... zs) const noexcept
    -> decltype(eve::negminabs(real(z0), real(zs)...))
    {
      return eve::minus(minabs[Options()](z0, zs...));
    }

    template<concepts::real V0, concepts::real... Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, Vs... vs) const noexcept
    -> decltype( eve::negminabs(v0, vs...))
    { return eve::negminabs[Options()](v0,vs...); }

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
//!
//!  @godbolt{doc/negminabs.cpp}
//======================================================================================================================
  inline constexpr auto negminabs = eve::functor<negminabs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
