//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
namespace kyosu::tags
{
  struct callable_pow: eve::elementwise
  {
    using callable_tag_type = callable_pow;

    KYOSU_DEFERS_CALLABLE(pow_);

    template < eve::floating_ordered_value U,  eve::ordered_value V>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , U const& v0
                                               , V const& v1) noexcept
    {
      if constexpr(eve::integral_value<V>)
        return eve::pow(v0, v1);
      else
      {
        auto fn = callable_pow{};
        return fn(kyosu::complex(v0), v1);
      }
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_pow(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow
//!   @brief Computes the  computing the pow operation \f$x^y\f$.
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
//!     constexpr auto pow(auto z0, auto z1) noexcept;               \\123
//!     constexpr auto pow(auto z0, eve::integral_value n)  noexcept; \\4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1`: Values to process.
//!
//!   **Return value**
//!      1. if both parameters are floating the call will act as if they were converted to complex before call
//!      2. if both parameters are floating or complex. The ieee specification are taken:\n
//!         In particular we have (IEC 60559):
//!
//!         * pow(+0, y), where y is a negative odd integer, returns \f$+\infty\f$
//!         * pow(-0, y), where y is a negative odd integer, returns \f$-\infty\f$
//!         * pow(\f$\pm0\f$, y), where y is negative, finite, and is an even integer or a non-integer,
//!           returns \f$+\infty\f$
//!         * pow(\f$\pm0\f$, \f$-\infty\f$) returns \f$+\infty\f$
//!         * pow(+0, y), where y is a positive odd integer, returns +0
//!         * pow(-0, y), where y is a positive odd integer, returns -0
//!         * pow(\f$\pm0\f$, y), where y is positive non-integer or a positive even integer, returns +0
//!         * pow(-1,\f$\pm\infty\f$) returns 1
//!         * pow(+1, y) returns 1 for any y, even when y is NaN
//!         * pow(x, \f$\pm0\f$) returns 1 for any x, even when x is NaN
//!         * pow(x, y) returns NaN if x is finite and less than 0 and y is finite and non-integer.
//!         * pow(x, \f$-\infty\f$) returns \f$+\infty\f$ for any |x|<1
//!         * pow(x, \f$-\infty\f$) returns +0 for any |x|>1
//!         * pow(x, \f$+\infty\f$) returns +0 for any |x|<1
//!         * pow(x, \f$+\infty\f$) returns \f$+\infty\f$ for any |x|>1
//!         * pow(\f$-\infty\f$, y) returns -0 if y is a negative odd integer
//!         * pow(\f$-\infty\f$, y) returns +0 if y is a negative non-integer or even integer
//!         * pow(\f$-\infty\f$, y) returns \f$-\infty\f$ if y is a positive odd integer
//!         * pow(\f$-\infty\f$, y) returns \f$+\infty\f$ if y is a positive non-integer or even integer
//!         * pow(\f$+\infty\f$, y) returns +0 for any y less than 0
//!         * pow(\f$+\infty\f$, y) returns \f$+\infty\f$ for any y greater than 0
//!         * except where specified above, if any argument is NaN, NaN is returned
//!
//!      3. if any parameter as a dimensionnality greater yhan 2, the call is semantically equivalent
//!         to `kyosu::exp(z1*eve::log(z0))`
//!
//!      4. pow can accept an integral typed second parameter,  in this case it is the russian peasant algorithm
//!         that is used.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_pow pow = {};
}
