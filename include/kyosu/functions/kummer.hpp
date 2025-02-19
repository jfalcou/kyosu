//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/hyperg/hyp1_1.hpp>

namespace kyosu
{
  template<typename Options>
  struct kummer_t : eve::strict_elementwise_callable<kummer_t, Options>
  {
    template<typename Z, typename T1,  typename T2>
    constexpr KYOSU_FORCEINLINE
    auto operator()(Z z, T1 aa, T2 bb) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(kyosu::complex(z), a, b);
      else if constexpr(Options::contains(regularized))
      {
        using r_t = decltype(kumi::get<0>(aa)+kumi::get<0>(bb)+zz);
        r_t a = kumi::get<0>(aa);
        r_t b = kumi::get<0>(bb);
        using u_t = eve::underlying_type_t<r_t>;
        auto tol = eve::eps(eve::as<u_t>());
        constexpr size_t Maxit = 100000;
        auto anegint = kyosu::is_flint(a) && eve::is_lez(real(a));
        auto bnegint = kyosu::is_flint(b) && eve::is_lez(real(b));
        auto abnegint = (anegint && !bnegint) || (bnegint && anegint && (real(b) < real(a)));

        auto br_abnegint =  [&](){
          return kyosu::cinf(eve::as<r_t>());
        };

        auto br_anegint =  [&](){
          auto bz = kyosu::if_else(bnegint, b, zero);
          int n =  eve::maximum(-real(a));
          r_t a1(1), s(kyosu::tgamma_inv(b));
          for (size_t j=1; j <= n; ++j)
          {
            a1*=(kyosu::dec(a+j)/(kyosu::dec(bz+j)*j))*zz;
            s += a1;
          }
          return s;
        };

        auto br_bnegint =  [&](auto test1){
          auto z = kyosu::if_else(test, zz, zero);
          auto cinf =  kyosu::cinf(as(b));
          auto num = a;
          auto den = if_else(is_lez(b), tgamma(b));
          auto s1 = num/den;
          auto spred = kyosu::zero(eve::as(s1));
          auto smallp = kyosu::false_(as<r_t>());

          for(int j=1; j <Maxit ; ++j)
          {
            num = kyosu::dec(a+j)*z;
            den = j*if_else(is_lez(dec(b+j)), cinf, dec(b+j));
            spred = s1
            s1 = s1+num/den;
            auto small = (j > real(-b)) && (kyosu::linfnorm[kyosu::flat](spred-s1) < kyosu::linfnorm[kyosu::flat](spred)*tol);
            if (eve::all(small && smallp)) return s1;
          }
          return if_else(smallp, s1, allbits);
        };


        auto br_regular =  [&](auto test){
          auto z = kyosu::if_else(test,  zz, zero);
          auto r1 = a/b;
          auto r2 = kyosu::inc(a)/(2*kyosu::inc(b));
          r_t s1 = kyosu::inc(z*r1);
          r_t s2 = s1+kyosu::sqr(z)*(r1)*r2;
          r_t s3{};
          auto smallp = kyosu::false_(as<r_t>());

          for (size_t j=3; j <= Maxit; ++j)
          {
            auto r = kyosu::dec(a+j)/(j*kyosu::dec(b+j));
            s3 = s2 + (s2-s1)*r*z;
            auto small = kyosu::linfnorm[kyosu::flat](s3-s2) < kyosu::linfnorm[kyosu::flat](s1)*tol;
            if (eve::all(small && smallp)) return s3;
            s1 = s2;
            s2 = s3;
            smallp = small;
          }
          return if_else(smallp, s3*kyosu::tgamma_inv(b), allbits);
        };

        r_t r =  kyosu::nan(eve::as<r_t>());
        auto notdone = kyosu::is_nan(r);

        if( eve::any(notdone) )
        {
          notdone = next_interval(br_abnegint, notdone, abnegint, r);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_anegint, notdone, anegint, r);
            if( eve::any(notdone) )
            {
              notdone = last_interval(br_zero, notdone, r, notdone);
            }
          }
          return r;
        }
      }
    }
      else
      {
        return  _::hyperg(z, kumi::tuple{a}, kumi::tuple{b});
      }
    }
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var kummer_
//!   @brief Computes the kummer function (confluent hypergeometric function of the first kind) \f$M\f$ which is
//!    an other name for the hypergeometric function \f${}_1F_1\f$
//!
//!   **Defined in Header**
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
//!     constexpr auto kummer(auto z, auto a, auto b) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a`, `b`, `z`: real or complex inputs.
//!
//!   **Return value**
//!
//!        Returns the value at z of the Kummer function   with `a` and `b` parameters.
//!        The call `kummer(z, a, b)` is equivalent to `hypergeometric(z, kumi::tuple{a},  kumi::tuple{b})`
//!
//!
//!  @groupheader{External references}
//!   *  [DLMF: Kummer Functions](https://dlmf.nist.gov/13.2)
//!   *  [Wolfram MathWorld:Confluent Hypergeometric Function of the Second Kind ](https://mathworld.wolfram.com/ConfluentHypergeometricFunctionoftheSecondKind.html)
//!   *  [Wikipedia: Confluent hypergeometric function](https://en.wikipedia.org/wiki/Confluent_hypergeometric_function)
//!  @groupheader{Example}
//!  @godbolt{doc/kummer.cpp}
//======================================================================================================================
  inline constexpr auto kummer = eve::functor<kummer_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
