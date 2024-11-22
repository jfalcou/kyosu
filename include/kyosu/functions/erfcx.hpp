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
#include <kyosu/functions/faddeeva.hpp>

namespace kyosu
{
  template<typename Options>
  struct erfcx_t : eve::elementwise_callable<erfcx_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
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
        return kyosu::_::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::erfcx(v); }

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
//!      template<eve::ordered_value T>              constexpr auto erfcx(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto erfcx(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//! **Return value**
//!
//!   1. a real input z return eve::erfcx(z).
//!
//!   2. The value of the normalized complementary error function is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/erfcx.cpp}
//======================================================================================================================
  inline constexpr auto erfcx = eve::functor<erfcx_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto erfcx_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto realz = is_real(z);
      if (eve::all(realz))
        return complex(eve::erfcx(real(z)));
      else  if (eve::none(realz))
        return faddeeva(complex(-imag(z), real(z)));
      else
        return if_else(realz, complex(eve::erfcx(real(z))), faddeeva(complex(-imag(z), real(z))));
    }
    else
    {
      return cayley_extend(erfcx, z);
    }
  }
}
