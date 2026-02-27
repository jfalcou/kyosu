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
  template<typename Options> struct inject_t : eve::elementwise_callable<inject_t, Options, pedantic_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(inject_t, inject_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var inject
  //!   @brief inject a real in the complex plane a nan producing a fnan.
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
  //!     template<kyosu::concepts::cayley_dickson_like Z> constexpr complexify_t<Z> inject(Z z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     - same as `complex(z)` for real typed `z`, except that real nan produces
  //!       complex fnan if `pedantic option is used`and acts as identity on other cayley_dickson_like
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/inject.cpp}
  //======================================================================================================================
  inline constexpr auto inject = eve::functor<inject_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename R, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto inject_(KYOSU_DELAY(), O const&, R r) noexcept
  {
    if constexpr (concepts::real<R>)
    {
      if constexpr (O::contains(pedantic)) return kyosu::complex_t<R>(r, eve::is_nan(r).mask());
      else return kyosu::complex_t<R>(r, eve::zero(as(r)));
    }
    else return r;
  }
}
