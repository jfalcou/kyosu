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
#include <kyosu/functions/erf.hpp>
#include <kyosu/functions/muli.hpp>
#include <kyosu/functions/mulmi.hpp>



namespace kyosu
{
  template<typename Options>
  struct erfi_t : eve::elementwise_callable<erfi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        if (eve::all(is_real(z)))
          return complex((*this)(real(z)));
        else
          return mulmi(erf(muli(z)));
      }
      else
      {
        return _::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V z) const noexcept
    {
      auto over = eve::sqr(z) > 720;
      auto r = eve::inf(eve::as(z))*eve::sign(z);
      r = eve::if_else(over, r, -imag(kyosu::erf(complex(eve::zero(eve::as(z)), -z))));
      return complex(r);
    }

    KYOSU_CALLABLE_OBJECT(erfi_t, erfi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var erfi
//!   @brief Callable object computing The imaginary error function \f$ \displaystyle \mathrm{erfi}(z) = -i\mathrm{erf}(iz)\f$
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
//!      template<eve::ordered_value T>              constexpr auto erfi(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto erfi(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : complex or real value to process.
//!
//! **Return value**
//!
//!   Returns the imaginary error function \f$ \displaystyle \mathrm{erfi}(z) = -i\mathrm{erf}(iz)\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/erfi.cpp}
//======================================================================================================================
  inline constexpr auto erfi = eve::functor<erfi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
