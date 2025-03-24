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
#include <kyosu/functions/faddeeva.hpp>

namespace kyosu
{
  template<typename Options>
  struct erfcx_t : eve::elementwise_callable<erfcx_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z> )
        return eve::erfcx(z);
      else if constexpr(concepts::complex<Z> )
      {
        auto realz = is_real(z);
        if (eve::all(realz))
          return complex(eve::erfcx(real(z)));
        else  if (eve::none(realz))
          return faddeeva(muli(z));
        else
          return if_else(realz, complex(eve::erfcx(real(z))), faddeeva(muli(z)));
      }
      else
      {
        return _::cayley_extend(*this, z);
      }
    }

    KYOSU_CALLABLE_OBJECT(erfcx_t, erfcx_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var erfcx
//!   @brief Computes the normalized complementary error function
//!   \f$ \displaystyle \mbox{erfcx}(x) = e^{x^2} \mbox{erfc}(x)\f$.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto erfcx(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//! **Return value**
//!
//!   - A real input typed z calls eve::erfcx.
//!   - The value of the normalized complementary error function is returned.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Error function](https://en.wikipedia.org/wiki/Error_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/erfcx.cpp}
//======================================================================================================================
  inline constexpr auto erfcx = eve::functor<erfcx_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
