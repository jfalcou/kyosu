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
  template<typename Options> struct expm1_t : eve::elementwise_callable<expm1_t, Options, radpi_option, real_only_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z>
    operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(expm1_t, expm1_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var expm1
  //!   @brief Computes the exponential of the argument minus 1.
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
  //!      template<kyosu::concepts::cayley_dickson T> constexpr complexify<T> expm1(T z)            noexcept; //1
  //!      template<kyosu::concepts::cayley_dickson T> constexpr complexify<T> expm1[radpi](T z)     noexcept; //2
  //!      template<kyosu::concepts::real           T> constexpr T             expm1[real_only](T z) noexcept; //3
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     1. Returns the exponential of the argument minus 1.
  //!        Provisions are made to ensure good precision near zero.
  //!     2. z is multiplied by \f$pi\f$ on input
  //!     3. Equivalent to `eve::expm1` call.
  //!
  //!   @note As it is a function devoted to better precision, it admits no `raw` option
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/expm1.cpp}
  //======================================================================================================================
  inline constexpr auto expm1 = eve::functor<expm1_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{

  template<typename Z, eve::callable_options O>
  constexpr auto expm1_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr (concepts::real<Z>)
    {
      if constexpr (O::contains(real_only))
      {
        if constexpr (O::contains(radpi)) return eve::expm1(eve::pi(eve::as(z))*z);
        else return eve::expm1(z);
      }
      else
        return complex(kyosu::expm1[kyosu::real_only](z));
    }
    else if constexpr (kyosu::concepts::complex<Z>)
    {
      auto [rz, iz] = z;
      auto [siz, ciz] = eve::sincos[o](iz);
      auto cosm1 = eve::if_else(abs(ciz) < eve::pio_4(eve::as(iz)), eve::dec(ciz), -eve::sqr(siz) / (eve::inc(ciz)));
      auto r = eve::fma(kyosu::expm1[real_only][o](rz), ciz, cosm1);
      auto i = kyosu::exp[real_only][o](rz) * siz;
      r = eve::if_else(rz == eve::inf(eve::as(rz)) && eve::is_not_finite(iz), rz, r);
      return complex(r, eve::if_else(kyosu::is_real(z), eve::zero, i));
    }
    else
     return _::cayley_extend(kyosu::expm1[o], z);
  }
}
