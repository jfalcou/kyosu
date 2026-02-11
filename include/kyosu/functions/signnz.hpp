//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/is_nez.hpp>

namespace kyosu
{
  template<typename Options> struct signnz_t : eve::elementwise_callable<signnz_t, Options>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(signnz_t, signnz_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var signnz
  //!   @brief Computes tne normalized value z/abs(z) if z is not zero else the sign of the real part
  //!     as a cayley_dickson.
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <kyosu/functions.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signnzatures}
  //!
  //!   @code
  //!   namespace kyosu
  //!   {
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T signnz(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns the "signnz" of the argument i.e. its normalized value, and the non zero sign of
  //!     the real part if the input is zero.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/signnz.cpp}
  //======================================================================================================================
  inline constexpr auto signnz = eve::functor<signnz_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr Z signnz_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (kyosu::concepts::real<Z>) return eve::signnz(z);
    else return kyosu::if_else(kyosu::is_nez(z), z / abs(z), eve::signnz(real(z)));
  }
}
