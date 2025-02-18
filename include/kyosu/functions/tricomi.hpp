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
        r_t zz(z);
        r_t aa(a);
        r_t bb(b);
        r_t ombb = oneminus(bb);
        r_t incaambb = inc(aa-bb);

        auto f1 = tgamma(dec(bb))*tgamma_inv(aa);
        auto f2 = tgamma(ombb)*tgamma_inv(inc(a-b));
        auto p  = pow(z, ombb);

        return f1*p*hypergeometric(zz, kumi::tuple{incaambb}, kumi::tuple{r_t(2)-bb})+
          f2*hypergeometric(zz, kumi::tuple{aa}, kumi::tuple{bb});
      }
    }
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tricomi_
//!   @brief Computes the tricomi function also called confluent hypergeometric function of the second kind
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
//!     * `a`, * `b`, `z`: real or complex inputs
//!
//!   **Return value**
//!
//!        Returns the value at z of the confluent hypergeometric function of the second kind with a and b parameters
//!
//!  @groupheader{External references}
//!   *  [DLMF: Legendre,F"(Bs Integrals](https://dlmf.nist.gov/19.2#ii)
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
