//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/types/complex.hpp>

namespace kyosu::tags
{
  struct callable_cinf : eve::elementwise
  {
    using callable_tag_type = callable_cinf;

    KYOSU_DEFERS_CALLABLE(i_);

    template<eve::value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, as<T> const& ) noexcept
    requires(concepts::cayley_dickson<T> || eve::floating_ordered_value<T>)
    {
      using u_t = eve::underlying_type_t<T>;
      return kyosu::complex(eve::nan(as<u_t>()),eve::inf(as<u_t>()));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_abs(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var i
//!   @brief Computes the complex number cinf i.e. complex(nan, inf) in the chosen type.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr as_complex_t<underlying_type_t<T>>  cinf(as<T> z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr és_complex_t<underlying_type_t<T>>  cinf(as<T> z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * always returns a complex scalar value cinf such that real(cinf) is a Nan  and imag(cinf) is Inf.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/i.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cinf cinf = {};
}
