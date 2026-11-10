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
#include <kyosu/functions/muli.hpp>

namespace kyosu
{
  template<typename Options> struct signnz_t : eve::elementwise_callable<signnz_t, Options, raw_option, pedantic_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_ABI constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z> KYOSU_ABI constexpr Z operator()(Z const& z, Z ifzero_val) const noexcept
    {
      return KYOSU_CALL(z, ifzero_val);
    }

    KYOSU_CALLABLE_OBJECT(signnz_t, signnz_);
  };

  //======================================================================================================================
  //! @defgroup signnz kyosu::signnz
  //! @ingroup agnostic
  //! @brief Computes tne normalized value z/abs(z) if z is not zero else the sign of the real part
  //!        as a cayley_dickson.
  //! @{
  //!   @var signnz
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T signnz(T z ) noexcept;
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T signnz(T z, T ifzero_value ) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns the "signnz" of the argument i.e. its normalized value, and a 'ifzero_value` of norm one if the input is zero.
  //!      * By default the `ifzero value for non Real types is i*sgn(real(z)) (i*i == -1).
  //!      * As this choice is not the only possible as soon as the input is not Real, a second parameter allows to choose
  //!        a different value for this case  which will be normalized before use.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt_todo{doc/signnz.cpp}
  //======================================================================================================================
  inline constexpr auto signnz = eve::functor<signnz_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O> constexpr Z signnz_(KYOSU_DELAY(), O const&, Z z, Z ifzero_val) noexcept
  {
    if constexpr (kyosu::concepts::real<Z>) return eve::signnz(z);
    else return kyosu::if_else(kyosu::is_nez(z), z / abs(z), ifzero_val / abs(ifzero_val));
  }

  template<typename Z, eve::callable_options O> constexpr Z signnz_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (kyosu::concepts::real<Z>) return eve::signnz(z);
    else return kyosu::if_else(kyosu::is_nez(z), z / abs(z), kyosu::muli(eve::signnz(real(z))));
  }
}
