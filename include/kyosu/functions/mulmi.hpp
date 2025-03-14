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
  struct mulmi_t : eve::elementwise_callable<mulmi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& c) const noexcept
    {
      if constexpr(kyosu::concepts::complex<Z>)
        return Z(ipart(c), -real(c));
      else if constexpr(kyosu::concepts::quaternion<Z>)
        return Z(ipart(c), -real(c), kpart(c), -jpart(c));
      else
        return mi(as(c))*c;
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return complex(zero(as(v)), -v); }

    KYOSU_CALLABLE_OBJECT(mulmi_t, mulmi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var mulmi
//!   @brief Computes the value of the parameter multiplied by i on the left side.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto  mulmi(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto  mulmi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * Returns `-i(as(z))*z`. If z is floating point a complex is returned,
//!       in the other cases the returned value has the same type as the input.
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
