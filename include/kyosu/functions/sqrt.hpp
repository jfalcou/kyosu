//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct sqrt_t : eve::elementwise_callable<sqrt_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return  KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(sqrt_t, sqrt_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sqrt
//!   @brief Computes a square root value.
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
//!      template<eve::floating_ordered_value T>     constexpr T sqrt(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr T sqrt(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr T sqrt(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to for which square root is computed.
//!
//!   **Return value**
//!
//!     1. a real typed input z is treated as if complex(z) was entered.
//!
//!     2. Returns the elementwise the square root of z,
//!        in the range of the right half-plane, including the imaginary axis (\f$[0, +\infty]\f$
//!        along the real axis and \f$[-\infty, +\infty]\f$ along the imaginary axis.)
//!
//!        *  The function is continuous onto the branch cut taking into account
//!           the sign of imaginary part
//!        *  eve::sqrt(kyosu::conj(z)) == kyosu::conj(kyosu::sqrt(z))
//!        *  If z is \f$\pm0\f$, the result is \f$+0\f$
//!        *  If z is \f$x+i \infty\f$, the result is \f$\infty+i \infty\f$ even if x is \f$NaN\f$
//!        *  If z is \f$x,NaN\f$, the result is \f$NaN,NaN\f$ (unless x is \f$\pm\infty\f$)
//!        *  If z is \f$-\infty+i y\f$, the result is \f$+0+i \infty\f$ for finite positive y
//!        *  If z is \f$+\infty+i y\f$, the result is \f$+\infty+i 0\f$ for finite positive y
//!        *  If z is \f$-\infty+i NaN\f$, the result is \f$NaN \pm i \infty\f$ (sign of imaginary part unspecified)
//!        *  If z is \f$+\infty+i NaN\f$, the result is \f$+\infty+i NaN\f$
//!        *  If z is \f$NaN+i y\f$, the result is \f$NaN+i NaN\f$
//!        *  If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!     2. Returns a square root of z.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sqrt.cpp}
//======================================================================================================================
  inline constexpr auto sqrt = eve::functor<sqrt_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sqrt_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      //always compute the sqrt of the complex with positive imaginary part
      //then conjugate if necessary
      auto [rz, iz] = z;
      auto negimag = eve::is_negative(iz);
      auto x = eve::abs(rz);
      auto y = eve::abs(iz);
      auto iaz = eve::if_else(negimag, -iz, iz); // always >= 0 or -Nan
      auto gtxy = (x > y);
      auto gezrz = eve::is_gez(rz);
      auto r = eve::if_else(gtxy, y/x, x/y);
      auto rr= eve::sqrt(eve::inc(eve::sqr(r)));
      auto sqrtx = eve::sqrt(x);
      auto w = eve::if_else(gtxy,
                            sqrtx*eve::sqrt(eve::half(eve::as(r))*eve::inc(rr)),
                            eve::sqrt(y)*eve::sqrt(eve::half(eve::as(r))*(r+rr)));
      auto is_real_z = kyosu::is_real(z);

      auto rr1 = eve::if_else(is_real_z, sqrtx, w);
      auto ii1 = eve::if_else(is_real_z, eve::zero, iaz*eve::half(eve::as(r))/w);
      Z res = kyosu::if_else(gezrz
                          , Z(rr1, ii1)
                          , Z(ii1, rr1)
                          );
      res = if_else(is_pure(z), eve::sqrt_2(eve::as(r))*Z( eve::half(eve::as(r)),  eve::half(eve::as(r)))*eve::sqrt(iz), res);
      if (eve::any(is_not_finite(z)))
      {
        res = kyosu::if_else(rz == eve::minf(eve::as(rz))
                            , kyosu::if_else( eve::is_nan(iz), Z(iz, eve::minf(eve::as(rz)))
                                            , Z(eve::zero(eve::as(rz)), eve::inf(eve::as(rz))))
                            , res
                            );
        res = kyosu::if_else(rz == eve::inf(eve::as(rz))
                            , if_else( eve::is_nan(iz), Z(eve::inf(eve::as(rz)), iz)
                                     , Z( eve::inf(eve::as(rz)), eve::zero(eve::as(rz)) ))
                            , res
                            );
        res = kyosu::if_else(eve::is_nan(rz), Z(rz, rz), res);
        auto infty = eve::inf(eve::as(iaz));
        res = kyosu::if_else(iaz == infty,  Z(infty, infty), res);
      }
      return if_else(negimag, kyosu::conj(res), res);
    }
    else
    {
      return cayley_extend(sqrt, z);
    }
  }
}
