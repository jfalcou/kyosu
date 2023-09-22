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
  struct callable_deta : eve::elementwise
  {
    using callable_tag_type = callable_deta;

    KYOSU_DEFERS_CALLABLE(deta_);

    template<eve::unsigned_scalar_value K, eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, K const & k, T const& v) noexcept
    {
      auto fn = callable_deta{};
      return fn(k, complex(v));
    }

    template<typename K, typename T>
    KYOSU_FORCEINLINE auto operator()(K const & target1, T const& target2) const noexcept -> decltype(eve::tag_invoke(*this, target1, target2))
    {
      return eve::tag_invoke(*this, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_deta(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var deta
//!   @brief Computes the Dirichlet sums \f$ \displaystyle \sum_0^\infty \frac{(-1)^n}{(kn+1)^z}\f$.
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
//!      template<unsigned_scalar_value K, eve::ordered_value T>       constexpr auto deta(K, k, T z) noexcept;  //1
//!      template<unsigned_scalar_value K, kyosu::concepts::complex T> constexpr auto deta(K, k, T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `k` : scalar unsigned value,  parameter of the sum.
//!     * `z` : Vcomplex or real value to process.
//!
//! **Return value**
//!
//!   Returns the Dirichlet sum \f$  \displaystyle \sum_0^\infty \frac{(-1)^n}{(kn+1)^z}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/deta.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_deta deta = {};
}
