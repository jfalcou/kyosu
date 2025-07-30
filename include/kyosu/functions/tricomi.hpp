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

namespace kyosu
{
  template<typename Options>
  struct tricomi_t : eve::strict_elementwise_callable<tricomi_t, Options>
  {
    template<concepts::complex_like Z, concepts::complex_like T1, concepts::complex_like T2>
    constexpr KYOSU_FORCEINLINE
    as_cayley_dickson_t<complexify_t<Z>, T1, T2> operator()(Z z, T1 a, T2 b) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(kyosu::complex(z), a, b);
      else
        return  KYOSU_CALL(z, a, b);
    }

    KYOSU_CALLABLE_OBJECT(tricomi_t, tricomi_);
  };

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
//!
//!  @groupheader{External references}
//!   *  [DLMF: Kummer Functions](https://dlmf.nist.gov/13.2)
//!   *  [Wolfram MathWorld:Confluent Hypergeometric Function of the Second Kind](https://mathworld.wolfram.com/ConfluentHypergeometricFunctionoftheSecondKind.html)
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
    using r_t = as_cayley_dickson_t<complexify_t<Z>, T1, T2>;
    using er_t = eve::element_type_t<r_t>;
    using u_t =  eve::element_type_t<as_real_type_t<r_t>>;
    r_t aa(a);
    r_t bb(b);
    auto bpflint = kyosu::is_real(bb) && eve::is_flint(kyosu::real(bb)) && eve::is_gtz(kyosu::real(bb));
    auto zlarge = kyosu::abs(z) > u_t(50);
    auto tol = eve::eps(eve::as<u_t>());


    auto br_bpflint =  [aa, bb, bpflint, tol](auto z){ //b is positive and flint
      auto n = eve::if_else(bpflint, real(bb), eve::one);
      auto fac = eve::sign_alternate(n)*kyosu::tgamma_inv(kyosu::inc(aa-n));
      // assume n is flint > 0 and a is not flint
      // tricomi is the sum of 3 terms multiplied by a common factor
      // common factor : \f$(-1)^n / \Gamma(a-n+1) \$n
      // first term    : \f$ \frac{\log(z)}{\Gamma(n)}{}_1F_1(a; n; z)\f$
      // second term   : \f$ \sum_0^\infty \frac{(a)_k(\psi(a+k)-\psi(k+1)-\psi(k+n))z^k}{(k+n-1)! k!}\f$
      // third term    : \f$-\sum_1^{n-1}  \frac{(k-1)!z^{k-1}}{(1-a)_k(n-k-1)!}\f$

      auto t1 =  kyosu::log(z)*tgamma_inv(n)*_::hyperg(z, kumi::tuple{aa}, kumi::tuple{n});//first term

      auto br_t2 = [aa, n, tol](auto zz){ //second term
        auto z = zz; //kyosu::if_else(test,  zz, zero);
        auto ak = aa;
        r_t fac = kyosu::tgamma_inv(n);
        auto haa = aa;
        auto h1  = u_t(1);
        auto hn  = n;
        auto daa = kyosu::digamma(haa);
        auto d1  = kyosu::digamma(h1);
        auto dn  = kyosu::digamma(hn);
         auto s = fac*(daa-d1-dn); //(kyosu::digamma(aa)-kyosu::digamma(u_t(1))-kyosu::digamma(n));
        constexpr int Maxit = 500;
        auto small = kyosu::false_(eve::as(z));

        for (size_t k = 1; k <= Maxit; ++k)
        {
          fac *= (ak/((n+k-1)*k))*zz;
          auto rk = kyosu::rec(u_t(k));
          daa += kyosu::rec(haa++);
          d1  += eve::rec(h1++);
          dn  += kyosu::rec(hn++);
          auto t = fac*(daa-d1-dn); //*(kyosu::digamma(aa+k)-kyosu::digamma(u_t(k+1))-kyosu::digamma(n+k));
          s+= if_else(small, zero, t);
          small = kyosu::linfnorm[kyosu::flat](t) <= kyosu::linfnorm[kyosu::flat](s)*tol;
          if (eve::all(small)) return s;
          ak = kyosu::inc(ak);
        }
        return kyosu::fnan(eve::as(z));
      };

      auto br_t3 = [aa, n](auto iz){ //third term
        auto oma = kyosu::oneminus(aa);
        auto s =  kyosu::zero(kyosu::as(iz));
        auto k = 1;
        auto test =  k < n;
        auto aak = kyosu::oneminus(aa);
        while (eve::any(test))
        {
          auto t = tgamma(u_t(k))*pow(iz, k)/(aak*tgamma(n-k));
          s -= kyosu::if_else(test, t, zero);
          ++k;
          test =  k < n;
          aak*= (oma+k-1);
        }
        return s;
      };
      return  fac*(t1+br_t2(z)+br_t3(kyosu::rec(z)));
    };


    auto br_large =  [aa, bb, zlarge, tol](auto iz){ //z is large
      iz = kyosu::if_else(zlarge, iz, zero);
      auto fac = kyosu::pow(iz, aa);
      auto ak = aa;
      auto ambp1k = kyosu::inc(aa-bb);
      int k = 1;
      auto t = fac;
      auto s = t;
      auto test = kyosu::false_(eve::as(iz));
      while (true)
      {
        t *= -(ak/k++)*ambp1k*iz;
        s += kyosu::if_else(test, zero, t);
        test = kyosu::linfnorm[kyosu::flat](t) <= kyosu::linfnorm[kyosu::flat](s)*tol;
        if (eve::all(test)) break;
        ++ak;
        ++ambp1k;
      }
      return s;
    };

    auto br_else =  [aa, bb](auto z){ //is_not_real(bb) || is_not_flint(bb)
      r_t ombb = oneminus(bb);
      r_t incaambb = inc(aa-bb);

      auto f1 = kyosu::tgamma(dec(bb))*tgamma_inv(aa);
      auto f2 = kyosu::tgamma(ombb)*tgamma_inv(inc(aa-bb));
      auto p  = pow(z, ombb);
      return f1*p*_::hyperg(z, kumi::tuple{incaambb}, kumi::tuple{2-bb})+
      f2*_::hyperg(z, kumi::tuple{aa}, kumi::tuple{bb});
    };

    r_t zzz(z);

    auto r = kyosu::fnan(eve::as<r_t>());
    auto notdone = kyosu::is_not_fnan(zzz);
    if( eve::any(notdone) )
    {
      notdone = next_interval(br_large, notdone, zlarge, r, kyosu::rec(zzz));
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_bpflint, notdone, bpflint, r, zzz);
        if( eve::any(notdone) )
        {
          if( eve::any(notdone) ) { last_interval(br_else, notdone, r, zzz); }
        }
      }
    }
    return r;
  }
}
