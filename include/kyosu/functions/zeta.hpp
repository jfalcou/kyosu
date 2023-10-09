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
  struct callable_zeta : eve::elementwise
  {
    using callable_tag_type = callable_zeta;

    KYOSU_DEFERS_CALLABLE(zeta_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_zeta{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const & target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_zeta(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var zeta
//!   @brief Computes the Riemann \f$ \displaystyle\zeta(z)=\sum_0^\infty \frac{1}{(n+1)^z}\f$.
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
//!      template<eve::floating_ordered_value T> constexpr auto zeta(T z) noexcept;
//!      template<kyosu::concepts::complex T>    constexpr auto zeta(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : value to process.
//!
//! **Return value**
//!
//!   Returns the Dirichlet zeta sum: \f$  \displaystyle \sum_0^\infty \frac{1}{(n+1)^z}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/zeta.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_zeta zeta = {};
}
