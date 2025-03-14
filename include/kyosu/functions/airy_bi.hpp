//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct airy_bi_t : eve::elementwise_callable<airy_bi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(kyosu::concepts::complex<Z> )
        return _::bi(z);
      else
        return _::cayley_extend(*this, z);
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::airy_bi(v); }

    KYOSU_CALLABLE_OBJECT(airy_bi_t, airy_bi_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var airy_bi
//!   @brief Computes the airy function \f$Bi\f$
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
//!      template<eve::floating_ordered_value T>     constexpr auto airy_bi(T z) noexcept;
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
//!     * returns  \f$Bi(z)\f$.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Airy Functions](https://mathworld.wolfram.com/AiryFunctions.html)
//!   *  [Wikipedia: Airy function](https://en.wikipedia.org/wiki/Airy_function)
//!   *  [DLMF: Airy and Related Functions](https://dlmf.nist.gov/9)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/airy_bi.cpp}
//======================================================================================================================
  inline constexpr auto airy_bi = eve::functor<airy_bi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
