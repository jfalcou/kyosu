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

namespace kyosu
{
  template<typename Options>
  struct airy_bi_t : eve::elementwise_callable<airy_bi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::airy_bi(v); }

    KYOSU_CALLABLE_OBJECT(airy_bi_t, airy_bi_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var airy_bi
//!   @brief Computes the airy function \f$Bi\f$,
//!
//!   **Defined in header**
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
//!      template<eve::floating_ordered_value T> constexpr auto airy_bi(T z) noexcept;
//!
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto airy_bi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$\{Bi(z)\}f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/airy_bi.cpp}
//======================================================================================================================
  inline constexpr auto airy_bi = eve::functor<airy_bi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto airy_bi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return bi(z);
    }
    else
    {
      return cayley_extend(airy_bi, z);
    }
  }
}
