//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/types/complex.hpp>
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct make_complex_t : eve::callable<make_complex_t, Options>
  {
    template<concepts::complex Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<eve::floating_value T>
    KYOSU_FORCEINLINE constexpr complex_t<T> operator()(T r)  const noexcept
    {
      return KYOSU_CALL(r);
    }

    template<eve::floating_value R, eve::floating_value I>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_n_t<2,R,I> operator()(R r,I i) const noexcept
    {
      return KYOSU_CALL(r,i);
    }

    KYOSU_CALLABLE_OBJECT(make_complex_t, make_complex_);
  };

//====================================================================================================================
//! @addtogroup functions
//! @{
//!   @var complex
//!   @brief Constructs a kyosu::complex_t instance
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
//!     constexpr auto complex(eve::floating_value auto r, eve::floating_value auto i = 0)  noexcept;
//!     constexpr T complex(kyosu::concepts::complex auto z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`      : Complex value.
//!     * `r`, `i` : Real and imaginary part used to construct a @ref kyosu::complex..
//!
//!   **Return value**
//!
//!     Returns a @ref kyosu::complex constructed from its arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/to_complex.cpp}
//======================================================================================================================

inline constexpr auto complex = eve::functor<make_complex_t>;
//====================================================================================================================
//! @}
//====================================================================================================================
}

namespace kyosu::_
{
  template<typename R, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto make_complex_(KYOSU_DELAY(), O const&, R v) noexcept
  {
    if constexpr(eve::floating_value<R>)  return as_cayley_dickson_n_t<2,R>(v, R{0});
    else                                  return v;
  }

  template<typename R, typename I, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto make_complex_(KYOSU_DELAY(), O const&, R r, I i) noexcept
  {
    return as_cayley_dickson_n_t<2,R,I>{r, i};
  }
}
