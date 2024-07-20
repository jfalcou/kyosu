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
  struct conj_t : eve::elementwise_callable<conj_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept { return KYOSU_CALL(v); }

    KYOSU_CALLABLE_OBJECT(conj_t, conj_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var conj
//!   @brief Computes the conjugate value.
//!
//!   **Defined in Header**
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
//!      template<concepts::cayley_dickson T> constexpr T conj(T z) noexcept;
//!      template<concepts::real T>           constexpr T conj(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to conjugate.
//!
//!   **Return value**
//!
//!     Returns the conjugate of its argument. i.e. the value with the same [real](@ref kyosu::real ) part
//!     and the opposite [pure](@ref kyosu::imag ) part.
//!
//!     For real inputs the call reduces to identity.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/conj.cpp}
//! @}
//======================================================================================================================
inline constexpr auto conj = eve::functor<conj_t>;
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto conj_(KYOSU_DELAY(), O const&, Z const& v) noexcept
  {
    if constexpr(concepts::cayley_dickson<Z>)
    {
      return Z{kumi::map_index([]<typename I>(I, auto m) { if constexpr(I::value>0) return -m; else return m;}, v)};
    }
    else return v;
  }
}
