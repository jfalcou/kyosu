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

namespace kyosu
{
  template<typename Options>
  struct tricomi_t : eve::strict_elementwise_callable<tricomi_t, Options>
  {
    template<concepts::cayley_dickson_like Z, concepts::cayley_dickson_like T1, concepts::cayley_dickson_like T2>
    KYOSU_FORCEINLINE constexpr auto  operator()( Z const& z, T1 const& t1,  T2 const & t2) const noexcept -> complexify_t<decltype(z+t1+t2)>
    {
      if constexpr(concepts::real<Z>)
        return (*this)[this->options()](kyosu::complex(z), t1, t2);
      else
        return KYOSU_CALL(z, t1, t2);
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
    using r_t = as_cayley_dickson_like_t<T1, T2, Z>;
    using u_t = eve::underlying_type_t<Z>;
    r_t zz(z);
    r_t aa(a);
    r_t bb(b);
    r_t ombb = oneminus(bb);
    r_t incaambb = inc(aa-bb);

    auto f1 = kyosu::tgamma(dec(bb))*tgamma_inv(aa);
    auto f2 = kyosu::tgamma(ombb)*tgamma_inv(inc(aa-bb));
    auto p  = pow(z, ombb);
    return f1*p*_::hyperg(zz, kumi::tuple{incaambb}, kumi::tuple{2-bb})+
      f2*_::hyperg(zz, kumi::tuple{aa}, kumi::tuple{bb});
  }
}
