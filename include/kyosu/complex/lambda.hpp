//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_lambda : eve::elementwise
  {
    using callable_tag_type = callable_lambda;

    KYOSU_DEFERS_CALLABLE(lambda_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_lambda{};
      return fn(to_complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const & target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_lambda(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lambda
//! @brief Callable object computing The Dirichlet \f$ \displaystyle \lambda(z) = \sum_0^\infty \frac{1}{(2n+1)^z}\f$
//!
//! This function can be extended to the whole complex plane as \f$\lambda(z) = \zeta(z)(1-2^{-x})\f$
//! (where \f$\zeta\f$ is the Riemann zeta function). It coincides with the serie where the serie converges.
//! However for `z = 1` the result is \f$\infty\f$.
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
//!      template<unsigned_scalar_value K, eve::ordered_value T>       constexpr auto lambda(K, k, T z) noexcept;  //1
//!      template<unsigned_scalar_value K, kyosu::concepts::complex T> constexpr auto lambda(K, k, T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Vcomplex or real value to process.
//!
//! **Return value**
//!
//!    Returns the Dirichlet sum \f$  \displaystyle \sum_0^\infty \frac{1}{(2n+1)^z}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lambda.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_lambda lambda = {};
}
