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
#include <kyosu/functions/exp_i.hpp>
#include <kyosu/functions/from_polar.hpp>
#include <kyosu/functions/is_real.hpp>
#include <kyosu/functions/log_abs.hpp>
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/is_eqz.hpp>
#include <kyosu/functions/sqr.hpp>
#include <kyosu/functions/convert.hpp>

namespace kyosu
{
  template<typename Options>
  struct pow_t : eve::strict_elementwise_callable<pow_t, Options>
  {

    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson <Z1>)
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept
    { return KYOSU_CALL(z0,z1); }

    template<concepts::real V0, eve::integral_value V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept -> decltype(v0+v1)
    { return eve::pow(v0, v1); }

    template<concepts::real V0, concepts::real V1>
    requires(!eve::integral_value<V1>)
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept ->complex_t<decltype(v0+v1)>
    { return (*this)(complex(v0),v1); }

    KYOSU_CALLABLE_OBJECT(pow_t, pow_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow
//!   @brief Computes the  computing the pow operation \f$x^y\f$.
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
//!     constexpr auto pow(auto z0, auto z1) noexcept;                \\123
//!     constexpr auto pow(auto z0, eve::integral_value n)  noexcept; \\4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!      1. if both parameters are floating the call will act as if they were converted to complex before call
//!      2. if both parameters are floating or complex. The ieee specification are taken:\n
//!         In particular we have (IEC 60559):
//!
//!         * pow(+0, y), where y is a negative odd integer, returns \f$+\infty\f$
//!         * pow(-0, y), where y is a negative odd integer, returns \f$-\infty\f$
//!         * pow(\f$\pm0\f$, y), where y is negative, finite, and is an even integer or a non-integer,
//!           returns \f$+\infty\f$
//!         * pow(\f$\pm0\f$, \f$-\infty\f$) returns \f$+\infty\f$
//!         * pow(+0, y), where y is a positive odd integer, returns +0
//!         * pow(-0, y), where y is a positive odd integer, returns -0
//!         * pow(\f$\pm0\f$, y), where y is positive non-integer or a positive even integer, returns +0
//!         * pow(-1,\f$\pm\infty\f$) returns 1
//!         * pow(+1, y) returns 1 for any y, even when y is NaN
//!         * pow(x, \f$\pm0\f$) returns 1 for any x, even when x is NaN
//!         * pow(x, y) returns NaN if x is finite and less than 0 and y is finite and non-integer.
//!         * pow(x, \f$-\infty\f$) returns \f$+\infty\f$ for any |x|<1
//!         * pow(x, \f$-\infty\f$) returns +0 for any |x|>1
//!         * pow(x, \f$+\infty\f$) returns +0 for any |x|<1
//!         * pow(x, \f$+\infty\f$) returns \f$+\infty\f$ for any |x|>1
//!         * pow(\f$-\infty\f$, y) returns -0 if y is a negative odd integer
//!         * pow(\f$-\infty\f$, y) returns +0 if y is a negative non-integer or even integer
//!         * pow(\f$-\infty\f$, y) returns \f$-\infty\f$ if y is a positive odd integer
//!         * pow(\f$-\infty\f$, y) returns \f$+\infty\f$ if y is a positive non-integer or even integer
//!         * pow(\f$+\infty\f$, y) returns +0 for any y less than 0
//!         * pow(\f$+\infty\f$, y) returns \f$+\infty\f$ for any y greater than 0
//!         * except where specified above, if any argument is NaN, NaN is returned
//!
//!      3. if any parameter as a dimensionality greater than 2, the call is semantically equivalent
//!         to `exp(z1*log(z0))`
//!
//!      4. pow can accept an integral typed second parameter,  in this case it is the russian peasant algorithm
//!         that is used (feasible as every monogen ideals are commutative).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: complex pow](https://en.cppreference.com/w/cpp/numeric/complex/pow)
//!   *  [Wolfram MathWorld: Power](https://mathworld.wolfram.com/Power.html)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow.cpp}
//======================================================================================================================
  inline constexpr auto pow = eve::functor<pow_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename C0,  typename C1, eve::callable_options O>
  constexpr auto pow_(KYOSU_DELAY(), O const&, C0 c0,  C1 c1) noexcept
  {
    using r_t = kyosu::as_cayley_dickson_t<C0,C1>;
    using er_t = eve::element_type_t<r_t>;
    using u_t  = eve::underlying_type_t<er_t>;
    if constexpr(eve::integral_value<C1>)
    {
      if constexpr( eve::unsigned_value<C1> )
      {
        if constexpr(kyosu::concepts::complex<C0>)
        {
          C0 base = c0;
          C1 expo = c1;
          auto const o = eve::one(eve::as<u_t>());
          r_t result(o);
          while(true)
          {
            if  (eve::all(eve::is_eqz(expo))) break;
            result = kyosu::if_else(eve::is_odd(expo), result*base, o);
            expo = (expo >> 1);
            base = kyosu::sqr(base);
          }
          return result;
        }
        else
        {
          return cayley_extend(pow, c0, c1);
        }
      }
      else
      {
        using ic1_t = eve::as_integer_t<C1, unsigned>;
        auto tmp = kyosu::pow(c0, eve::bit_cast(eve::abs(c1), eve::as<ic1_t>()));
        return kyosu::if_else(eve::is_ltz(c1), kyosu::rec(tmp), tmp);
      }
    }
    else if constexpr((dimension_v<C0> <= 2) && (dimension_v<C1> <= 2))
    {
      r_t r;
      if constexpr(kyosu::concepts::real<C0> && kyosu::concepts::complex<C1>) // c1 is complex c0 is real
      {
        auto [rc1, ic1] = c1;
        auto lgac0 = eve::log_abs(c0);
        auto ang = eve::if_else(kyosu::is_real(c1), eve::zero, ic1*lgac0);
        auto mod = eve::pow(c0, rc1);
        auto r1 = kyosu::from_polar(mod, ang);
        auto isposc0 = eve::is_positive(c0);
        if (eve::all(isposc0))
        {
          r = r1;
        }
        else
        {
          auto rho = eve::exp(eve::diff_of_prod(lgac0, rc1, ic1, eve::pi(eve::as(rc1))));
          auto theta = eve::sum_of_prod[eve::pedantic](eve::pi(eve::as(rc1)), rc1, ic1, lgac0);
          auto r2 = rho*kyosu::exp_i(theta);
          r = kyosu::if_else(isposc0, r1, r2);
        }
      }
      else if constexpr(kyosu::concepts::real<C1> ) // c0 is complex c1 is real
      {
        return exp(c1*log(c0));
      }
      else if constexpr( kyosu::concepts::complex<C0>)// c0 and c1 are complex
      {
        auto  [rc1, ic1] = c1;
        auto lc0 = kyosu::log_abs[eve::pedantic](c0);
        auto argc0 = kyosu::arg(c0);
        auto rho = eve::exp(eve::diff_of_prod[eve::pedantic](lc0, rc1, ic1, argc0));
        auto theta = eve::sum_of_prod[eve::pedantic](argc0, rc1, ic1, lc0);
        r = kyosu::if_else(is_eqz(rho), rho, rho*exp_i(theta));
      }
      r = kyosu::if_else(kyosu::is_eqz(c1), eve::one(eve::as<u_t>()), r);
      return r;
    }
    else
    {
      if constexpr(kyosu::concepts::real<C1>) //c0 cayley c1 real
      {
        return cayley_extend(pow, c0, c1);
      }
      else if  constexpr(kyosu::concepts::real<C0>)//c1 cayley c0 real
      {
        return cayley_extend_rev(pow, c0, c1);
      }
      else
      {
        auto cc0 = kyosu::convert(c0, eve::as<er_t>());
        auto cc1 = kyosu::convert(c1, eve::as<er_t>());

        auto r = kyosu::exp(kyosu::log(cc0)*cc1);
        return kyosu::if_else (kyosu::is_eqz(cc0)
                              , eve::if_else(kyosu::is_eqz(cc1)
                                            , eve::one(eve::as<u_t>())
                                            , eve::zero(eve::as<u_t>()))
                              , r
                              );
      }
    }
  }
}
