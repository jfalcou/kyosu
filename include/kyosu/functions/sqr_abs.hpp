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
  template<typename Options> struct sqr_abs_t : eve::elementwise_callable<sqr_abs_t, Options, pedantic_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(sqr_abs_t, sqr_abs_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var sqr_abs
  //!   @brief Computes the squared sqr_absolute value of the parameter.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr as_real_type_t<T>  sqr_abs(T z)           noexcept; //1
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr as_real_type_t<T>  sqr_abs[pedantic](T z) noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     1. Returns the squared modulus of its argument, a floating value.
  //!     2. Returns inf as soon as the sum of the non-nan squared components is infinite
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/sqr_abs.cpp}
  //======================================================================================================================
  inline constexpr auto sqr_abs = eve::functor<sqr_abs_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sqr_abs_(KYOSU_DELAY(), O const&, Z v) noexcept
  {
    if constexpr (concepts::real<Z>) return eve::sqr(v);
    else if constexpr (O::contains(pedantic))
    {
      if constexpr (concepts::complex<Z>)
      {
        auto [r, i] = v;
        auto r2 = eve::sqr(r);
        auto i2 = eve::sqr(i);
        return eve::if_else(eve::is_infinite(r2) || eve::is_infinite(i2), eve::inf(as(r)), i2 + r2);
      }
      else
      {
        auto nanfound = eve::false_(as<Z>());
        auto squares = kumi::map(
          [&nanfound](auto const& e) {
            auto nanfound = eve::is_nan(e);
            return if_else(nanfound, eve::zero, eve::sqr(e));
          },
          v);
        auto r = kumi::sum(kumi::extract(squares, kumi::index<1>), get<0>(squares));
        return if_else(is_infinite(r), eve::inf(as(r)), if_else(nanfound, eve::allbits, r));
      }
    }
    else
    {
      if constexpr (concepts::complex<Z>)
      {
        auto [r, i] = v;
        return eve::sqr(r) + eve::sqr(i);
      }
      else
      {
        auto squares = kumi::map([](auto const& e) { return eve::sqr(e); }, v);
        return kumi::sum(kumi::extract(squares, kumi::index<1>), get<0>(squares));
      }
    }
  }
}
