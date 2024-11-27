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
#include <kyosu/functions/abs.hpp>

namespace kyosu
{
  template<typename Options>
  struct maxabs_t : eve::strict_elementwise_callable<maxabs_t, Options, eve::numeric_option, eve::pedantic_option>
  {
    template<typename Z0, typename ...Zs>
    requires(concepts::cayley_dickson<Z0> || (concepts::cayley_dickson<Zs>|| ...))
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0  const & z0, Zs const & ... zs) const noexcept
    -> decltype(eve::maxabs(real(z0), real(zs)...))
    {  return eve::sqrt(eve::max[this->options()](kyosu::sqr_abs(z0), kyosu::sqr_abs(zs)...)); }

    template<concepts::real V0, concepts::real... Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, Vs... vs) const noexcept -> decltype( eve::maxabs(v0, vs...))
    { return eve::maxabs[this->options()](v0,vs...); }

    KYOSU_CALLABLE_OBJECT(maxabs_t, maxabs_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var maxabs
//!   @brief Callable object computing the maxabs operation.
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
//!      template<typename ... Ts> auto maxabs(Ts ... zi ) const noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns elementwise  the maximum of the absolute values of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/maxabs.cpp}
//======================================================================================================================
  inline constexpr auto maxabs = eve::functor<maxabs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
