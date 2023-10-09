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
  struct callable_eta : eve::elementwise
  {
    using callable_tag_type = callable_eta;

    KYOSU_DEFERS_CALLABLE(eta_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_eta{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const & target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_eta(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var eta
//!   @brief Computes the Dirichlet sum \f$ \displaystyle \sum_0^\infty \frac{(-1)^n}{(n+1)^z}\f$.
//!   Sometimes this function is for obvious reasons called the alternative \f$\zeta\f$ function .
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
//!      template<unsigned_scalar_value K, eve::ordered_value T>              constexpr auto eta(T z) noexcept;  //1
//!      template<unsigned_scalar_value K, kyosu::concepts::cayley_dickson T> constexpr auto eta(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : value to process.
//!
//! **Return value**
//!
//!   Returns the Dirichlet alternating zeta function: \f$  \displaystyle \sum_0^\infty \frac{(-1)^n}{(n+1)^z}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/eta.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_eta eta = {};
}
