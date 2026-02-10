//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options> struct radinpi_t : eve::elementwise_callable<radinpi_t, Options>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(radinpi_t, radinpi_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var radinpi
  //!   @brief Computes the parameter divided by \f$\pi\f$.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr as_real_type_t<T> radinpi(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns  argument divided by \f$\pi\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/radinpi.cpp}
  //======================================================================================================================
  inline constexpr auto radinpi = eve::functor<radinpi_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto radinpi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (concepts::real<Z>) return eve::radinpi(z);
    else return inv_pi(eve::as(z)) * z;
  }
}
