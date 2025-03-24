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

namespace kyosu
{
  template<typename Options>
  struct hypot_t : eve::strict_elementwise_callable<hypot_t, Options, eve::pedantic_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like ...Zs>
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 z0, Zs ... zs) const noexcept -> decltype(eve::hypot(real(z0), real(zs)...))
    {       return eve::hypot[this->options()](kumi::flatten(kumi::make_tuple(z0, zs...))); }

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
