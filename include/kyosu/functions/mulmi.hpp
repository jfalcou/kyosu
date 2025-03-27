//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/constants/mi.hpp>

namespace kyosu
{
  template<typename Options>
  struct mulmi_t : eve::elementwise_callable<mulmi_t, Options
                                            , eve::left_option, eve::right_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(mulmi_t, mulmi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var mulmi
//!   @brief Computes the value of the parameter multiplied by -i on the left or right side.
//!   For real, complex and quaternion the computation is an optimization over the call to * operator.
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
//!   {  // regular call
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto  mulmi(T z)        noexcept; //1
//!
//!      // Semantic modifyer
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto  mulmi[left}(T z)  noexcept; //1
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto  mulmi[right](T z) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. Returns `mi(as(z))*z` If z is floating point a complex is returned,
//!     2. Returns `z*mi(as(z))` If z is floating point a complex is returned,
//!       Of course the option has no effect on real or complex inputs.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/mulmi.cpp}
//======================================================================================================================
  inline constexpr auto mulmi = eve::functor<mulmi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  constexpr auto mulmi_(KYOSU_DELAY(), O const&o, Z z) noexcept
  {
    if constexpr(kyosu::concepts::real<Z>)         return complex(zero(as(z)), -z);
    else if constexpr(kyosu::concepts::complex<Z>) return Z(ipart(z), -real(z));
    else if constexpr(O::contains(eve::right))
    {
      if constexpr(kyosu::concepts::quaternion<Z>) return Z(ipart(z), -real(z), -kpart(z), +jpart(z));
      else                                         return z**kyosu::mi(as(z));
    }
    else
    {
      if constexpr(kyosu::concepts::quaternion<Z>) return Z(ipart(z), -real(z), kpart(z), -jpart(z));
      else                                         return kyosu::mi(as(z))*z;
    }
  }
}

