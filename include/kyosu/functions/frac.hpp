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
  template<typename Options> struct frac_t : eve::elementwise_callable<frac_t, Options>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(frac_t, frac_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var frac
  //!   @brief Computes the frac value.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T frac(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns the fractionnal part of its argument. i.e. the value whose parts are the fractionnal
  //!     parts of the original ones.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/frac.cpp}
  //======================================================================================================================
  inline constexpr auto frac = eve::functor<frac_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto frac_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (kyosu::concepts::real<Z>) return eve::frac(z);
    else return Z{kumi::map([](auto const& e) { return eve::frac(e); }, z)};
  }
}
