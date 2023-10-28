//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/bessel.hpp>

namespace kyosu::tags
{
  struct callable_cyl_lbessel_in: eve::elementwise
  {
    using callable_tag_type = callable_cyl_lbessel_in;

    KYOSU_DEFERS_CALLABLE(cyl_lbessel_in_);

    template<eve::ordered_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& v) noexcept {
      callable_cyl_lbessel_in fn{};
      return fn(n, complex(v));
    }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_lbessel_in(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @brief Computes the logarithm of the Bessel functions of the first kind,
//!   \f$ I_{n}(z)\f$.
//!
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_lbessel_in(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_lbessel_in(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * return the logarithm of \f$I_n(z)\f$.
//!
//!  @warning Up to now the cayley_dickson versions have only been implemented for scalar int values of n.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_lbessel_in.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_lbessel_in cyl_lbessel_in = {};
}
