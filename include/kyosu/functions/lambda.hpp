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
  template<typename Options> struct lambda_t : eve::elementwise_callable<lambda_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr (concepts::real<Z>) return (*this)(complex(z));
      else return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(lambda_t, lambda_);
  };
  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var lambda
  //! @brief Callable object computing The Dirichlet \f$ \displaystyle \lambda(z) = \sum_0^\infty \frac{1}{(2n+1)^z}\f$
  //!
  //! This function can be extended to the whole complex plane as \f$\lambda(z) = \zeta(z)(1-2^{-z})\f$
  //! (where \f$\zeta\f$ is the Riemann zeta function). It coincides with the serie where the serie converges.
  //! However for `z = 1` the result is \f$\infty\f$.
  //! The usual extension mechanism is used for general Cayley-dickson input values.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> lambda(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z` : cayley_dickson or real value to process.
  //!
  //! **Return value**
  //!
  //!    Returns the Dirichlet sum \f$  \displaystyle \sum_0^\infty \frac{1}{(2n+1)^z}\f$
  //!
  //!  @note λ can be used as an alias in code.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Dirichlet lambda](https://mathworld.wolfram.com/DirichletLambdaFunction.html)
  //!   *  [Wikipedia: Dirichlet series](https://en.wikipedia.org/wiki/Dirichlet_series)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/lambda.cpp}
  //======================================================================================================================
  inline constexpr auto lambda = eve::functor<lambda_t>;
  inline constexpr auto λ = eve::functor<tgamma_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr Z lambda_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (concepts::complex<Z>)
    {
      auto zz = exp2(z);
      auto k = (z - 1) / (z - 2);
      auto r = if_else(z == complex(eve::one(eve::as(real(z)))), complex(eve::inf(eve::as(real(z)))), k * deta(1u, zz));
      imag(r) = eve::if_else(is_real(z), eve::zero, imag(r));
      return r;
    }
    else return kyosu::_::cayley_extend(kyosu::lambda, z);
  }
}
