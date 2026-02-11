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
  template<typename Options> struct is_not_cinf_t : eve::elementwise_callable<is_not_cinf_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return eve::is_not_nan(kyosu::arg(z)) || eve::is_not_infinite(kyosu::abs(z));
      ;
    }

    template<concepts::real V> KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept
    {
      return eve::true_(eve::as(v));
    }

    KYOSU_CALLABLE_OBJECT(is_not_cinf_t, is_not_cinf_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var is_not_cinf
  //!   @brief test if the parameter is a not `cinf`.
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
  //!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_not_cinf(T z) noexcept; /1
  //!      template<eve::floating_ordered_value T>     constexpr auto is_not_cinf(T z) noexcept; /2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns elementwise false is the absolute value is not infinite or the argument is a not NaN.
  //!     This is test a quantity with infinite magnitude, but undetermined complex phase.
  //!     This is always false for real entries.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: complex infinity](https://reference.wolfram.com/language/ref/ComplexInfinity.html)
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/is_not_cinf.cpp}
  //======================================================================================================================
  inline constexpr auto is_not_cinf = eve::functor<is_not_cinf_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
