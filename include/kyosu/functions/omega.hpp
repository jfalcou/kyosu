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
#include <kyosu/functions/exp2.hpp>
#include <kyosu/functions/deta.hpp>

namespace kyosu
{
  template<typename Options> struct omega_t : eve::elementwise_callable<omega_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr (concepts::real<Z>) return (*this)(complex(z));
      else return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(omega_t, omega_);
  };
  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var omega
  //!   @brief Computes the Wright \f$\omega\f$ the inverse function of \f$ x \rightarrow \log  x+x\f$
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <eve/module/special.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      // Regular overload
  //!      constexpr auto omega(complex_like auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto omega[conditional_expr auto c](complex_like auto x) noexcept; // 2
  //!      constexpr auto omega[logical_value auto m](complex_like auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: [complex_like](@ref eve::value).
  //!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. The value of the Wright \f$\omega\f$ function is returned
  //!        (the inverse function of \f$ x \rightarrow \log x+x\f$) is returned.
  //!        is the input is a real value a complex value is returned.
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!     ω can be used as an alias.
  //!
  //!  @groupheader{External references}
  //!   *  [Wikipedia: Wright omega function](https://en.wikipedia.org/wiki/Wright_omega_function)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/omega.cpp}
  //================================================================================================
  inline constexpr auto omega = eve::functor<omega_t>;
  inline constexpr auto ω = eve::functor<omega_t>;
  //================================================================================================
  //! @}
  //======================================================================================================================
}

// This implementation is adapted from
// Algorithm 917: Complex Double-Precision Evaluation of the Wright ~ Function
// Authors: Piers W. Lawrence, Robert M. Corless, David J. JeffreyAuthors Info & Claims
// ACM Transactions on Mathematical Software (TOMS), Volume 38, Issue 3

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto omega_(KYOSU_DELAY(), O const&, Z zz) noexcept
  {
    if constexpr (concepts::complex<Z>)
    {
      using u_t = eve::underlying_type_t<Z>;
      auto x = kyosu::real(zz);
      auto y = kyosu::imag(zz);
      auto e = kyosu::zero(kyosu::as(zz));
      auto r = kyosu::zero(kyosu::as(zz));
      auto pi = eve::pi(kyosu::as(x));
      auto pio2 = eve::pio_2(kyosu::as(x));
      auto ipi = kyosu::muli(pi);
      auto I = kyosu::i(kyosu::as(zz));
      auto s = kyosu::one(kyosu::as(x));
      auto singular = (x == eve::mone(eve::as(x))) && (eve::abs(y) == pi);
      auto notdone = is_not_infinite(zz) && is_not_nan(zz) && !singular;
      auto notalreadydone = notdone;
      auto w = kyosu::fnan(kyosu::as(zz));
      // Signed zeros between branches
      auto inftest = (eve::is_minf(x) && (-pi < y) && (y <= pi));
      w = if_else(inftest, sign(pio2 - y) * zero(eve::as(y)), w);
      w += kyosu::muli(eve::bitofsign(y));
      auto ympi = y - pi;
      auto yppi = y + pi;
      auto near = u_t(0.1e-1);
      w = if_else(eve::is_pinf(x) || eve::is_infinite(y), zz, w);
      w = if_else(singular, kyosu::mone(kyosu::as(zz)), w);

      constexpr u_t half = eve::half(eve::as<u_t>());
      constexpr u_t third = eve::third(eve::as<u_t>());
      constexpr u_t thotw = 3 * half;
      constexpr u_t inv36(1.0 / 36.0);
      constexpr u_t inv270(1.0 / 270.0);
      constexpr u_t inv4320(1.0 / 4320.0);

      if (eve::any(notdone))
      {
        auto t1 = ((-2 < x && x <= 1 && 1 < y && y < 2 * pi));
        auto t2 = ((-2 < x && x <= 1 && -2 * pi < y && y < -1));
        // Choose approximation based on region
        //=====================================
        // Region 1/2: upper/lower branch point
        // Series about z=-1+Pi*I or  z=-1-Pi*I
        //=====================================
        auto br_12 =
          [&](auto z,
              auto sgn) { // ((-2.0<x && x<=1.0 && 1.0<y && y< 2.0*pi)) || ((-2.0<x && x<=1.0 && 1.0<y && y< 2.0*pi))
            auto pz = kyosu::conj(kyosu::sqrt(kyosu::conj(2 * (z + 1 + sgn * ipi))));
            return r = kyosu::reverse_horner(pz, mone(as(x)), -I * sgn, third, sgn * inv36 * I, inv270, inv4320 * I);
          };
        //===============================
        // Region 3: between branch cuts
        // Serie: About -infinity
        //===============================
        auto br_3 = [&](auto z) { // (x <= -2.0 && -pi < y && y <= pi)
          auto pz = kyosu::exp(z);
          return kyosu::reverse_horner(pz, one(as(x)), mone(as(x)), thotw, u_t(-8.0 / 3.0), u_t(125.0 / 24.0)) * pz;
        };
        //======================
        // Region 4: Mushroom
        // Series about z=1
        //======================
        auto br_4 = [&](auto z) { // (((-2.0 < x) && (x<=1.0) && (-1.0 <= y) && (y <= 1.0))
          //    || ((-2.0 < x) && (x-0.1e1)*(x-0.1e1)+y*y<=pi*pi))
          auto pz = kyosu::dec(z);
          return fam(half, half, z) + kyosu::reverse_horner(pz, u_t(1.0 / 16.0), u_t(-1.0 / 192.0), u_t(-1.0 / 3072.0),
                                                            u_t(13.0 / 61440.0)) *
                                        sqr(pz);
        };
        //======================
        // Region 5: Top wing
        // Negative log series
        //======================
        auto br_5 = [&](auto z) { // (x<=-0.105e1 && pi<y && y-pi<=-0.75e0*(x+0.1e1))
          auto t = z - ipi;
          auto pz = kyosu::log(-t);
          auto r00 = kyosu::reverse_horner(pz, eve::one(as<u_t>()), -thotw, third);
          auto r11 = fma(fam(mone(as<u_t>()), half, pz), pz, reverse_horner(t, pz, -pz, one(as<u_t>())) * t) * t;
          return fma(r00, pz, r11) / (kyosu::sqr(t) * t);
        };
        //======================
        // Region 6: Bottom wing
        // Negative log series
        //======================
        auto br_6 = [&](auto z) { // (x<=-0.105e1 && 0.75e0*(x+0.1e1)< y+pi && y+pi<0.0e0)
          auto t = z + ipi;
          auto pz = kyosu::log(-t);
          return ((1 + (-thotw + third * pz) * pz) * pz + ((-1 + half * pz) * pz + (pz + (-pz + t) * t) * t) * t) /
                 (t * t * t);
        };
        //================================
        // Region 7: Everywhere else
        // Series solution about infinity
        //================================
        auto br_7 = [&](auto z) { // else
          auto pz = kyosu::log(z);
          return ((1 + (-thotw + third * pz) * pz) * pz + ((-1 + half * pz) * pz + (pz + (-pz + z) * z) * z) * z) /
                 (z * z * z);
        };

        if (eve::any(notdone))
        {
          auto sgn = if_else(t2, eve::one, mone(eve::as(x)));
          notdone = next_interval(br_12, notdone, (t1 || t2), w, zz, sgn);
          if (eve::any(notdone))
          {
            auto t3 = (x <= -2 && -pi < y && y <= pi);
            notdone = next_interval(br_3, notdone, t3, w, zz);
            if (eve::any(notdone))
            {
              auto t4 = ((-2 < x) && (x <= 1) && (-1 <= y) && (y <= 1));
              notdone = next_interval(br_4, notdone, t4, w, zz);
              if (eve::any(notdone))
              {
                auto t5 = (x <= -0.105e1 && pi < y && y - pi <= u_t(-0.75) * (x + 0.1e1));
                notdone = next_interval(br_5, notdone, t5, w, zz);
                if (eve::any(notdone))
                {
                  auto t6 = (x <= u_t(-0.105e1) && u_t(0.75) * (x + 1) < y + pi && y + pi < 0);
                  notdone = next_interval(br_6, notdone, t6, w, zz);
                  if (eve::any(notdone)) { notdone = last_interval(br_7, notdone, w, zz); }
                }
              }
            }
          }
        }
      }
      //================================
      // Regularize if near branch cuts
      //================================
      auto regul = [&](auto z, auto test) {
        auto pid = eve::pi[lower](eve::as(x));
        auto piu = eve::pi[upper](eve::as(x));
        s = if_else(test, -s, s);
        auto regulm = [&](auto test1) {
          /* Recompute ympi with directed rounding */
          auto nympi = eve::sub[upper](y, pid);
          nympi = eve::if_else(eve::is_lez(ympi), eve::sub[lower](y, pi), ympi);
          auto res = complex(x, kyosu::if_else(test1, nympi, ympi));
          return res;
        };
        auto regulp = [&](auto test2) {
          /* Recompute yppi with directed rounding */
          auto nyppi = eve::add[upper](y, piu);
          nyppi = eve::if_else(eve::is_lez(yppi), eve::add[lower](y, pi), yppi);
          return complex(x, kyosu::if_else(test2, nyppi, yppi));
        };
        auto test1 = eve::abs(ympi) <= near;
        return if_else(test, if_else(test1, regulm(test1), regulp(!test1)), z);
      };

      auto test = notalreadydone && (x <= -0.1e1 + near && (eve::abs(ympi) <= near || eve::abs(yppi) <= near));
      auto regulzz = regul(zz, test);
      if (eve::any(test)) zz = if_else(notalreadydone, if_else(test, regulzz, zz), zz);

      //===============
      // Iteration one
      //===============
      if (eve::any(notalreadydone))
      {
        auto w1 = s * w;
        r = fam(zz, -s, w1) - kyosu::log(w1);
        auto wp1 = fma(s, w1, eve::one(eve::as(x)));
        e = r / wp1 * fms(2 * wp1, fam(wp1, u_t(2.0 / 3.0), r), r) / fms(2 * wp1, fam(wp1, u_t(2.0 / 3.0), r), 2 * r);
        w1 *= kyosu::inc(e);
        w = if_else(notalreadydone, w1, w);

        //===============
        // Iteration two
        //===============
        auto tmp = eve::sqr(kyosu::abs(wp1));
        if (eve::any(notalreadydone &&
                     (kyosu::abs(reverse_horner(w, 2, -8 * w, -1)) * eve::sqr(eve::sqr(kyosu::abs(r))) >=
                      eps(as(x)) * 72 * tmp * eve::sqr(tmp))))
        {
          r = fam(zz, -s, w) - kyosu::log(w);
          wp1 = fma(s, w, eve::one(eve::as(x)));
          e =
            r / wp1 * fms(2.0 * wp1, fam(wp1, u_t(2.0 / 3.0), r), r) / fms(2 * wp1, fam(wp1, u_t(2.0 / 3.0), r), 2 * r);
          w = if_else(notalreadydone, w * (1 + e), w);
        }
      }
      return s * w;
    }
    else return kyosu::_::cayley_extend(kyosu::omega, zz);
  }
}
