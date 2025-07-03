//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/hyperg/hyp1_1.hpp>
#include <kyosu/constants/fnan.hpp>
#include <kyosu/functions/is_not_fnan.hpp>
#include <kyosu/functions/is_not_flint.hpp>
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/tgamma.hpp>
#include <kyosu/functions/tgamma_inv.hpp>
#include <kyosu/functions/digamma.hpp>
#include <kyosu/functions/pow.hpp>
#include <eve/detail/hz_device.hpp>
#include <iostream>
#include <iomanip>
namespace kyosu
{
  template<typename Options>
  struct tricomi_t : eve::strict_elementwise_callable<tricomi_t, Options>
  {
    template<typename Z, typename T1,  typename T2>
    constexpr KYOSU_FORCEINLINE
    auto operator()(Z z, T1 a, T2 b) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(kyosu::complex(z), a, b);
      else
        return  KYOSU_CALL(z, a, b);
    }

    KYOSU_CALLABLE_OBJECT(tricomi_t, tricomi_);
  };

//  HypergeometricU[a, n, z] == ((-1)^n/Gamma[1 + a - n]) (
//  (Log[z]/(n - 1)!) Hypergeometric1F1[a, n, z]
//   - Sum[(k - 1)!/(z^k (Pochhammer[1 - a, k] (n - k - 1)!)), {k, 1, n - 1}] +
//   Sum[(Pochhammer[a, k]/((n + k - 1)! k!)) (PolyGamma[a + k] - PolyGamma[1 + k] - PolyGamma[n + k]) z^k, {k, 0, Infinity}]) /;
//  Element[n, Integers] && n > 0
//https://functions.wolfram.com/HypergeometricFunctions/HypergeometricU/06/01/03/02/
//https://functions.wolfram.com/HypergeometricFunctions/HypergeometricU/06/02/

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tricomi
//!   @brief Computes the tricomi function \f$U\f$ also called confluent hypergeometric
//!   function of the second kind
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
//!     constexpr auto tricomi(auto z, auto a, auto b) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a`, `b`, `z`: real or complex inputs.
//!
//!   **Return value**
//!
//!     Returns the value at z of the confluent hypergeometric function of the second kind
//!     with `a` and `b` parameters and non integral `b`
//!
//!  @groupheader{External references}
//!   *  [DLMF: Kummer Functions](https://dlmf.nist.gov/13.2)
//!   *  [Wolfram MathWorld:Confluent Hypergeometric Function of the Second Kind ](https://mathworld.wolfram.com/ConfluentHypergeometricFunctionoftheSecondKind.html)
//!   *  [Wikipedia: Confluent hypergeometric function](https://en.wikipedia.org/wiki/Confluent_hypergeometric_function)
//!  @groupheader{Example}
//!  @godbolt{doc/tricomi.cpp}
//======================================================================================================================
  inline constexpr auto tricomi = eve::functor<tricomi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, typename T1, typename T2, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto tricomi_(KYOSU_DELAY(), O const&, Z z, T1 a, T2 b) noexcept
  {
    using r_t = decltype(z+a+b);
    using u_t =  eve::underlying_type_t<r_t>;
    r_t aa(a);
    r_t bb(b);
    auto bpflint = kyosu::is_real(bb) && eve::is_flint(kyosu::real(bb)) && eve::is_gtz(kyosu::real(bb));

    auto br_bpflint =  [aa, bb, bpflint](auto z){ //br_bpflint
      auto n = eve::if_else(bpflint, real(bb), eve::one);
      auto fac = eve::sign_alternate(n)*kyosu::tgamma_inv(kyosu::inc(aa-n));
      std::cout << "fac global " << fac << std::endl;
      // assume n is flint > 0 and a is not flint
      // tricomi is the the of 3 terms multiplied by a common factor
      // common factor : \f$(-1)^n / \Gamma(a-n+1) \$n
      // first term    : \f$ \frac{\log(z)}{\Gamma(n)}{}_1F_1(a; n; z)\f$
      // second term   : \f$ \sum_0^\infty \frac{(a)_k(\psi(a+k)-\psi(k+1)-\psi(k+n))z^k}{(k+n-1)! k!}\f$
      // third term    : \f$-\sum_1^{n-1}  \frac{(k-1)!z^{k-1}}{(1_a)_k(n-k-1)!}\f$
      //


      auto t1 =  kyosu::log(z)*tgamma_inv(n)*_::hyperg(z, kumi::tuple{aa}, kumi::tuple{n});

//        std::cout << "aa  " << aa << std::endl;
//        std::cout << "n   " << n  << std::endl;
//        std::cout << "1F1 " << _::hyperg(z, kumi::tuple{aa}, kumi::tuple{n})<< std::endl;

      auto br_t3 = [aa, n](auto iz){
        auto oma = kyosu::oneminus(aa);
        auto s =  kyosu::zero(kyosu::as(iz));
        auto k = 1;
        auto test =  k < n;
        auto aak = kyosu::oneminus(aa);
         std::cout << "k   " << k   << std::endl;
         std::cout << "n   " << n   << std::endl;
         std::cout << "iz  " << iz  << std::endl;
//         std::cout << "oma " << oma << std::endl;
        while (eve::any(test))
        {
           std::cout << "aak   " << aak   << std::endl;
           std::cout << "  k   " <<   k   << std::endl;
//           std::cout << "oma " << oma << std::endl;

          auto t = tgamma(u_t(k))*pow(iz, k)/(aak*tgamma(n-k));
          std::cout << "t   " << t   << std::endl;
          s -= t;
          ++k;
          test =  k < n;
          std::cout << "tst " << test << std::endl;
          aak*= (oma+k-1);
        }
//         auto k = 0;
//         auto t = one(eve::as(iz));
//         auto test = k < n-1;
//         while (eve::any(test))
//         {
// //           std::cout << "k   " << k   << std::endl;
// //           std::cout << "oma " << oma << std::endl;
//           t *= (k)*iz/((oma+k)*(n-k));

//           s-= t;
//           ++k;
//           test =  k < n-1;

//           if (eve::all(test)) break;
//         }
        std::cout << "s   " << s   << std::endl;
        return s;
      };

      auto br_t2 = [aa, n](auto zz){
        auto tol = eve::eps(eve::as<u_t>());
        auto z = zz; //kyosu::if_else(test,  zz, zero);
        auto ak =aa;
        r_t fac = kyosu::tgamma_inv(n);
//        std::cout << "init fac   " << fac  << std::endl;
        auto s = fac*(kyosu::digamma(aa)-kyosu::digamma(u_t(1))-kyosu::digamma(n));
        std::cout << " ======  s " << s <<  std::endl;
        constexpr int Maxit = 500;
        auto small = kyosu::false_(eve::as(z));

        for (size_t k = 1; k <= Maxit; ++k)
        {
          fac *= (ak/((n+k-1)*k))*zz;
          auto t = fac*(kyosu::digamma(aa+k)-kyosu::digamma(u_t(k+1))-kyosu::digamma(n+k));
          s+= if_else(small, zero, t);
          small = kyosu::linfnorm[kyosu::flat](t) <= kyosu::linfnorm[kyosu::flat](s)*tol;
          if (eve::all(small)){
            std::cout << "t2 k   " <<  k << " -> s "<< s   << std::endl;
            return s;
          }
          ak = kyosu::inc(ak);
        }
        return kyosu::fnan(eve::as(z));
      };

      auto r =  t1;
      auto t2 = br_t2(z);
//        std::cout << "t1   " << t1   << std::endl;
      r+= t2;
      auto t3 = br_t3(kyosu::rec(z));
        std::cout << "t3   " << t3   << std::endl;
      r += t3;
      std::cout << "fac ici " << fac << std::endl;

      r*= fac;
//      std::cout << "r   " << r << std::endl;

      return  r; //kyosu::if_else(kyosu::is_real(z) && eve::is_ltz(real(z)), conj(r), r);

    };

    auto br_else =  [aa, bb](auto z){ //is_not_real(bb) || is_not_flint(bb)
      r_t ombb = oneminus(bb);
      r_t incaambb = inc(aa-bb);

      auto f1 = kyosu::tgamma(dec(bb))*tgamma_inv(aa);
      auto f2 = kyosu::tgamma(ombb)*tgamma_inv(inc(aa-bb));
      auto p  = pow(z, ombb);
      //        std::cout << std::setprecision(15) << "zz " << zz << std::endl;
//         std::cout << "aa " << aa << std::endl;
//         std::cout << "bb " << bb << std::endl;
//         std::cout << "f1 " << f1 << std::endl;
//         std::cout << "f2 " << f2 << std::endl;
//         std::cout << "p  " << p  << std::endl;
//         std::cout << "h1 " << _::hyperg(zz, kumi::tuple{incaambb}, kumi::tuple{2-bb}) << std::endl;
//         std::cout << "h2 " << _::hyperg(zz, kumi::tuple{aa}, kumi::tuple{bb}) << std::endl;
      return f1*p*_::hyperg(z, kumi::tuple{incaambb}, kumi::tuple{2-bb})+
      f2*_::hyperg(z, kumi::tuple{aa}, kumi::tuple{bb});
    };

    r_t zzz(z);
    auto r = kyosu::fnan(eve::as<r_t>());
    auto notdone = kyosu::is_not_fnan(zzz);
    if( eve::any(notdone) )
    {
      notdone = next_interval(br_bpflint, notdone, bpflint /* && (kyosu::is_not_flint(aa) || aa == kyosu::one(as(aa)))*/, r, zzz);
      if( eve::any(notdone) )
      {
        if( eve::any(notdone) ) { last_interval(br_else, notdone, r, zzz); }
      }
    }
    return r;
  }
}
