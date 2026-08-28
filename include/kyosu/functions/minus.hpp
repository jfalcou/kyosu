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
  template<typename Options> struct minus_t : eve::elementwise_callable<minus_t, Options, raw_option, pedantic_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(minus_t, minus_);
  };

  //======================================================================================================================
  //! @defgroup minus kyosu::minus
  //! @ingroup agnostic
  //! @brief Computes the opposite value.
  //! @{
  //!   @var minus
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
  //!      template<kyosu::concepts::cayley_dickson T> constexpr T minus(T z) noexcept;
  //!      template<eve::floating_ordered_value T>     constexpr T minus(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns the opposite of its argument.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/minus.cpp}
  //======================================================================================================================
  inline constexpr auto minus = eve::functor<minus_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr Z minus_(KYOSU_DELAY(), O const&, Z const& z) noexcept
  {
    return -z;
  }
}
