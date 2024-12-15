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
#include <kyosu/functions/oneminus.hpp>



namespace kyosu
{
  template<typename Options>
  struct digamma_t : eve::elementwise_callable<digamma_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return  (*this)(complex(v)); }

    KYOSU_CALLABLE_OBJECT(digamma_t, digamma_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var digamma
//!   @brief Computes the Digamma function i.e. the logarithmic derivative of the \f$\Gamma\f$ function
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
//!     constexpr auto  digamma(auto z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : value to process.
//!
//!   **Return value**
//!
//!     The value of the Digamma function: \f$\frac{\Gamma'(z)}{\Gamma(z)}\f$ is returned.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Digamma function](https://en.wikipedia.org/wiki/Digamma_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/digamma.cpp}
//======================================================================================================================
  inline constexpr auto digamma = eve::functor<digamma_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto digamma_(KYOSU_DELAY(), O const&, Z a0) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      // 15 sig. digits for 0<=real(z)<=171
      // coeffs should sum to about g*g/2+23/24
      //
      using r_t = eve::element_type_t<as_real_type_t<Z>>;
      auto  g=r_t(607)/r_t(128);
      // best results when 4<=g<=5
      constexpr int N = 15;
      std::array<r_t, N>  c =
        {  0.99999999999999709182,
           57.156235665862923517,
           -59.597960355475491248,
           14.136097974741747174,
           -0.49191381609762019978,
           .33994649984811888699e-4,
           .46523628927048575665e-4,
           -.98374475304879564677e-4,
           .15808870322491248884e-3,
           -.21026444172410488319e-3,
           .21743961811521264320e-3,
           -.16431810653676389022e-3,
           .84418223983852743293e-4,
           -.26190838401581408670e-4,
           .36899182659531622704e-5
        };

      //Num Recipes used g=5 with 7 terms
      //for a less effective approximation

      auto reflection = real(a0) < eve::half(eve::as(real(a0)));
      auto z = if_else(reflection, oneminus(a0), a0);

      Z d{};
      auto n = d;
      for(int pp = N-1; pp >= 1; --pp){
        auto dz = rec(z+eve::dec(pp));
        auto dd =  c[pp]*dz;
        d += dd;
        n -= dd*dz;
      }
      d+= c[0];
      auto zg = z+g-eve::half(eve::as(g));
      auto f = log(zg) + (n/d - g/zg);

      if(eve::any(reflection))
      {
        f = if_else(reflection, f-eve::pi(eve::as(g))*cotpi(a0), f);
        f = if_else (reflection && is_real(a0) && eve::is_flint(real(a0))
                    , complex(eve::nan(eve::as(g)), eve::inf(eve::as(g))), f);
      }
      return f;
    }
    else
    {
      return cayley_extend(digamma, a0);
    }
  }
}
