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
#include <kyosu/functions/acosh.hpp> 
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct asech_t : eve::elementwise_callable<asech_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(asech_t, asech_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asech
//!   @brief Computes the inverse  hyperbolic secant of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto asech(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto asech(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if complex(z) was entered.
//!
//!   2. Returns elementwise \f$\mathop{\mathrm{acosh}}(1/z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asech.cpp}
//======================================================================================================================
  inline constexpr auto asech = eve::functor<asech_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asech_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
   return kyosu::acosh(kyosu::rec(z));
  }
}
