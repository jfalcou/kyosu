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
  template<typename Options> struct make_complex_t : eve::callable<make_complex_t, Options>
  {
    template<concepts::complex Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& v) const noexcept { return v; }

    template<eve::floating_value T> KYOSU_FORCEINLINE constexpr complex_t<T> operator()(T r) const noexcept
    {
      return as_cayley_dickson_n_t<2, T>(r, T{0});
    }

    template<eve::floating_value R, eve::floating_value I>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_n_t<2, R, I> operator()(R r, I i) const noexcept
    {
      return as_cayley_dickson_n_t<2, R, I>{r, i};
    }

    KYOSU_CALLABLE_OBJECT(make_complex_t, make_complex_);
  };

  //====================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var complex
  //!   @brief Constructs a kyosu::complex_t instance
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
