//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/hyperg/hyp1_1.hpp>
#include <kyosu/functions/tgamma.hpp>
#include <kyosu/functions/tgamma_inv.hpp>
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
      {
        using r_t = decltype(z+a+b);
        using u_t =  eve::underlying_type_t<r_t>;
        auto opeps = 1+eve::eps(eve::as<u_t>())*10;
        r_t zz(z);
        r_t aa(a);
        r_t bb(b);
//        bb = if_else(kyosu::is_flint(bb), r_t(real(bb)*opeps), bb);
        r_t ombb = oneminus(bb);
        r_t incaambb = inc(aa-bb);

        auto f1 = kyosu::tgamma(dec(bb))*tgamma_inv(aa);
        auto f2 = kyosu::tgamma(ombb)*tgamma_inv(inc(aa-bb));
        auto p  = pow(z, ombb);
        std::cout << std::setprecision(15) << "zz " << zz << std::endl;
        std::cout << "aa " << aa << std::endl;
        std::cout << "bb " << bb << std::endl;
        std::cout << "f1 " << f1 << std::endl;
        std::cout << "f2 " << f2 << std::endl;
        std::cout << "p  " << p  << std::endl;
        std::cout << "h1 " << _::hyperg(zz, kumi::tuple{incaambb}, kumi::tuple{2-bb}) << std::endl;
        std::cout << "h2 " << _::hyperg(zz, kumi::tuple{aa}, kumi::tuple{bb}) << std::endl;
        return f1*p*_::hyperg(zz, kumi::tuple{incaambb}, kumi::tuple{2-bb}, kyosu::regularized)+
          f2*_::hyperg(zz, kumi::tuple{aa}, kumi::tuple{bb}, kyosu::regularized);
      }
    }
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
