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

namespace kyosu
{
  template<typename Options>
  struct hypot_t : eve::strict_elementwise_callable<hypot_t, Options, eve::pedantic_option>
  {
    template<typename Z0, typename ...Zs>
    requires(concepts::cayley_dickson<Z0>  || (concepts::cayley_dickson<Zs> || ...))
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 z0, Zs ... zs) const noexcept -> decltype(eve::hypot(real(z0), real(zs)...))
    { return KYOSU_CALL(z0,zs...); }

    template<concepts::real V0, concepts::real... Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, Vs... vs) const noexcept -> decltype( eve::manhattan(v0, vs...))
    { return eve::hypot(v0,vs...); }

    KYOSU_CALLABLE_OBJECT(hypot_t, hypot_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var hypot
//!   @brief Callable object computing the hypot operation.
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
//!      template<typename ... Ts> auto hypot(Ts ... zi ) const noexcept                //1
//!      template<typename ... Ts> auto hypot[eve::pedantic](Ts ... zi ) const noexcept //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process: mix of floating and Cayley-Dickson.
//!
//!   **Return value**
//!
//!     1.  Returns \f$ \sqrt{\sum_{i = 0}^{n-1} |z_i|^2} \f$ where \f$n\f$ is the number of arguments.
//!     2.  provisions are made to avoid overflow and to return \f$\infty\f$ as soon as a parameter is infinite.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/hypot.cpp}
//======================================================================================================================
  inline constexpr auto hypot = eve::functor<hypot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z0, typename... Zs, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto hypot_(KYOSU_DELAY(), O const& o, Z0 z0, Zs... zs) noexcept
  {
   if constexpr(concepts::cayley_dickson<Z0> || (concepts::cayley_dickson<Zs> || ...) )
      return eve::hypot[o](kumi::flatten(kumi::make_tuple(z0, zs...)));
    else
      return eve::hypot[o](z0, zs...);
  }
}
