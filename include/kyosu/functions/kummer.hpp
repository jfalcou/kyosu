//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/hyperg/hyp1_1.hpp>
#include <kyosu/functions/tgamma_inv.hpp>

namespace kyosu
{
  template<typename Options>
  struct kummer_t : eve::strict_elementwise_callable<kummer_t, Options, regularized_option>
  {
    template<concepts::cayley_dickson_like Z, concepts::cayley_dickson_like T1, concepts::cayley_dickson_like T2>
    KYOSU_FORCEINLINE constexpr Z operator()( Z const& z, T1 const& t1,  T2 const & t2) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)[this->options](kyosu::complex(z), t1, t2);
      else
        return KYOSU_CALL(z, t1, t2);
    }

    KYOSU_CALLABLE_OBJECT(kummer_t, kummer_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var kummer
//!   @brief Computes the Kummer function (confluent hypergeometric function of the first kind) \f$M\f$ (which is
//!    an other name for the hypergeometric function \f${}_1F_1\f$) and it regularized version \f$\mathbf{M}\f$.
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
//!      //regular call
//!     constexpr auto kummer(auto z, auto a, auto b) noexcept;             //1
//!
//!      // Semantic modifyiers
//!     constexpr auto kummer[regularized](auto z, auto a, auto b) noexcept;//2
//!
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a`, `b`, `z`: real or complex inputs.
//!
//!   **Return value**
//!
//!     1. Returns the value at `z` of the Kummer function   with `a` and `b` parameters.
//!        The call `kummer(z, a, b)` is equivalent to `hypergeometric(z, kumi::tuple{a},  kumi::tuple{b})`
//!     2. With the regularized options, returns the value at `z` of the Regularized Kummer function \f$\mathbf{M}\f$,
//!        i.e. \f$M\f$ divided by \f$\Gamma(b)\f$, well defined even if `b` is a negative integer.
//!
//!  @groupheader{External references}
//!   *  [DLMF: Kummer Functions](https://dlmf.nist.gov/13.2)
//!   *  [Wolfram MathWorld:Confluent Hypergeometric Function of the Second Kind ](https://mathworld.wolfram.com/ConfluentHypergeometricFunctionoftheSecondKind.html)
//!   *  [Wikipedia: Confluent hypergeometric function](https://en.wikipedia.org/wiki/Confluent_hypergeometric_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/kummer.cpp}
//======================================================================================================================
  inline constexpr auto kummer = eve::functor<kummer_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, typename T1, typename T2, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto kummer_(KYOSU_DELAY(), O const&, Z zz, T1 aa, T2 bb) noexcept
  {
    if constexpr(O::contains(regularized))
    {
      using r_t = decltype((aa+bb)+zz);
      r_t a(aa);
      r_t b(bb);
      r_t z(zz);
      using u_t = eve::underlying_type_t<r_t>;
      auto tol = eve::eps(eve::as<u_t>());
      constexpr size_t Maxit = 100000;
      auto anegint = kyosu::is_flint(a) && eve::is_lez(real(a));
      auto bnegint = kyosu::is_flint(b) && eve::is_lez(real(b));
      b = if_else(bnegint, eve::next(real(b)), b);
      auto abnegint = (anegint && !bnegint) || (bnegint && anegint && (real(b) < real(a)));
      auto anegintnotb = anegint && !bnegint;

      auto br_abnegint =  [&](){
        return kyosu::zero(eve::as<r_t>());
      };

      auto br_anegintnotb =  [&](){
        auto bz = kyosu::if_else(bnegint, b, zero);
        int n =  eve::maximum(-real(a));
        r_t a1(1), s(kyosu::tgamma_inv(bz));
        for (size_t j=1; j <= n; ++j)
        {
          a1*=(kyosu::dec(a+j)/(kyosu::dec(bz+j)*j))*z;
          s += a1;
        }
        return s;
      };

      auto br_regular =  [&](auto test){
        auto z = kyosu::if_else(test,  zz, zero);
        auto r1 = a/b;
        auto r2 = kyosu::inc(a)/(2*kyosu::inc(b));
        r_t s1 = kyosu::inc(z*r1);
        r_t s2 = s1+kyosu::sqr(z)*(r1)*r2;
        r_t s3{};
        auto smallp = kyosu::false_(as<r_t>());
        auto gb = kyosu::tgamma_inv(b);
        for (size_t j=3; j <= Maxit; ++j)
        {
          auto r = kyosu::dec(a+j)/(j*kyosu::dec(b+j));
          s3 = s2 + (s2-s1)*r*z;
          auto small = kyosu::linfnorm[kyosu::flat](s3-s2) < kyosu::linfnorm[kyosu::flat](s1)*tol;
          if (eve::all(small && smallp)) return gb*s3;
          s1 = s2;
          s2 = s3;
          smallp = small;
        }
        return if_else(smallp, gb*s3, allbits);
      };

      r_t r =  kyosu::nan(eve::as<r_t>());
      auto notdone = kyosu::is_nan(r);

      if( eve::any(notdone) )
      {
        notdone = next_interval(br_abnegint, notdone, abnegint, r);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_anegintnotb, notdone, anegintnotb, r);
          if( eve::any(notdone) )
          {
            notdone = last_interval(br_regular, notdone, r, notdone);
          }
        }
        return r;
      }
    }
    else
    {
      return  _::hyperg(zz, kumi::tuple{aa}, kumi::tuple{bb});
    }
  }
}
