//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/is_pure.hpp>
#include <kyosu/constants/fnan.hpp>

namespace kyosu
{
  template<typename Options> struct sqrt_t : eve::strict_elementwise_callable<sqrt_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, concepts::real K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<kyosu::complexify_if_t<Options, Z>, K> operator()(
      Z const& z, K const& k) const noexcept
    requires(eve::same_lanes_or_scalar<Z, K>)
    {
      return KYOSU_CALL(z, k);
    }

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
  //!      //  regular call
  //!      constexpr auto sqrt(auto z)                                                    noexcept; //1
  //!      template<eve::value K> constexpr auto sqrt(auto z, K k)                        noexcept; //2
  //!
  //!      // semantic modifyers
  //!      template<eve::value K> constexpr auto sqrt[principal](\*any previus overload)  noexcept; //3
  //!      template<concepts::real T> constexpr auto sqrt[real_only](T z)                 noexcept; //1
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to for which square root is computed.
  //!     * `k`: index of the square root taken modulo 1.
  //!
  //!   **Return value**
  //!
  //!     1. With one parameter  returns the principal square root of `z` which has the same imaginary part sign as `z`.
  //!        * A real typed input z is treated as if `complex(z)` was entered, unless the option real_only is used
  //!          in which case the parameter must be a floating_value and the result will the same as a call to eve::rsqrt
  //!        * for complex input, returns elementwise the square root of z,
  //!          in the range of the right half-plane, including the imaginary axis (\f$[0, +\infty]\f$
  //!          along the real axis and \f$[-\infty, +\infty]\f$ along the imaginary axis.)
  //!
  //!        *  The function is continuous onto the branch cut taking into account
  //!           the sign of imaginary part
  //!        *  kyosu::sqrt(kyosu::conj(z)) == kyosu::conj(kyosu::sqrt(z))
  //!        *  If z is \f$\pm0\f$, the result is \f$+0\f$
  //!        *  If z is \f$x+i \infty\f$, the result is \f$\infty+i \infty\f$ even if x is \f$NaN\f$
  //!        *  If z is \f$x,NaN\f$, the result is \f$NaN,NaN\f$ (unless x is \f$\pm\infty\f$)
  //!        *  If z is \f$-\infty+i y\f$, the result is \f$+0+i \infty\f$ for finite positive y
  //!        *  If z is \f$+\infty+i y\f$, the result is \f$+\infty+i 0\f$ for finite positive y
  //!        *  If z is \f$-\infty+i NaN\f$, the result is \f$NaN \pm i \infty\f$ (sign of imaginary part unspecified)
  //!        *  If z is \f$+\infty+i NaN\f$, the result is \f$+\infty+i NaN\f$
  //!        *  If z is \f$NaN+i y\f$, the result is \f$NaN+i NaN\f$
  //!        *  If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
  //!     2. Returns the kth sqrt root of z, k is taken modulo 1; 0 is identical to 1. 1 gives the opposite root.
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference: complex cosh](https://en.cppreference.com/w/cpp/numeric/complex/sqrt)
  //!   *  [Wolfram MathWorld: Square Root](https://mathworld.wolfram.com/SquareRoot.html)
  //!   *  [Wikipedia: Square root](https://en.wikipedia.org/wiki/Square_root)
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
  KYOSU_FORCEINLINE constexpr auto sqrt_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr (O::contains(real_only) && concepts::real<Z>) return eve::sqrt[o.drop(real_only)](z);
    else if constexpr (concepts::real<Z>) return sqrt(complex(z));
    else if constexpr (kyosu::concepts::complex<Z>)
    {
      if (eve::all(is_real(z)))
      {
        auto rz = kyosu::real(z);
        auto sqt = eve::sqrt(eve::abs(rz));
        return eve::if_else(is_nan(real(z)), kyosu::fnan(as(z)),
                            eve::if_else(eve::is_positive(rz), kyosu::complex(sqt, zero(eve::as(sqt))),
                                         kyosu::complex(zero(eve::as(sqt)), eve::signnz(kyosu::imag(z)) * sqt)));
      }
      else
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
        auto r = eve::if_else(gtxy, y / x, x / y);
        auto rr = eve::sqrt(eve::inc(eve::sqr(r)));
        auto sqrtx = eve::sqrt(x);
        auto w = eve::if_else(gtxy, sqrtx * eve::sqrt(eve::half(eve::as(r)) * eve::inc(rr)),
                              eve::sqrt(y) * eve::sqrt(eve::half(eve::as(r)) * (r + rr)));
        auto is_real_z = kyosu::is_real(z);

        auto rr1 = eve::if_else(is_real_z, sqrtx, w);
        auto ii1 = eve::if_else(is_real_z, eve::zero, iaz * eve::half(eve::as(r)) / w);
        Z res = kyosu::if_else(gezrz, Z(rr1, ii1), Z(ii1, rr1));
        res = if_else(is_pure(z),
                      eve::sqrt_2(eve::as(r)) * Z(eve::half(eve::as(r)), eve::half(eve::as(r))) * eve::sqrt(y), res);
        if (eve::any(is_not_finite(z)))
        {
          res = kyosu::if_else(rz == eve::minf(eve::as(rz)),
                               kyosu::if_else(eve::is_nan(iz), Z(iz, eve::minf(eve::as(rz))),
                                              Z(eve::zero(eve::as(rz)), eve::inf(eve::as(rz)))),
                               res);
          res = kyosu::if_else(
            rz == eve::inf(eve::as(rz)),
            if_else(eve::is_nan(iz), Z(eve::inf(eve::as(rz)), iz), Z(eve::inf(eve::as(rz)), eve::zero(eve::as(rz)))),
            res);
          res = kyosu::if_else(eve::is_nan(rz), Z(rz, rz), res);
          auto infty = eve::inf(eve::as(iaz));
          res = kyosu::if_else(iaz == infty, Z(infty, infty), res);
        }
        return if_else(negimag, kyosu::conj(res), res);
      }
    }
    else { return cayley_extend(kyosu::sqrt, z); }
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sqrt_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  {
    if constexpr (O::contains(real_only))
    {
      if constexpr (concepts::real<Z>) return eve::sign_alternate(k) * eve::sqrt(z);
      else return sqrt[o.drop(real_only)](z, k);
    }
    else if constexpr (concepts::real<Z>) return sqrt(complex(z), k);
    else return eve::sign_alternate(k) * kyosu::sqrt[o](z);
  }

  template<concepts::real Z, eve::value... K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sqrt_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), sqrt(z, k...));
  }
}
