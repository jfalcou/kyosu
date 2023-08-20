//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      T abs(T x) noexcept;                  //1
//!
//!      template< eve::floating_value T >
//!      T abs(eve::as_complex<T> z) noexcept; //2
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!     * `z` :  [complex argument ](@ref eve::complex).
//!
//!    **Return value**
//!
//!    1.  value containing the [elementwise](@ref glossary_elementwise)
//!        absolute value of `x` if it is representable in this type.
//!
//!        More specifically, for signed integers : the absolute value of eve::valmin
//!        is not representable and the result is undefined.
//!
//!
//!    2.
//!
//!  @warning
//!        abs is also a standard library function name and there possibly
//!        exists a C macro version which may be called instead of the EVE version.
//!        To avoid confusion, use the eve::abs notation.
//!


//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_abs : eve::elementwise
  {
    using callable_tag_type = callable_abs;

    KYOSU_DEFERS_CALLABLE(abs_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::abs(v); }

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
//!   @var abs
//!   @brief Computes the absolute value of the parameter.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr as_real_t<T> abs(T z) noexcept;
//!      template<eve::ordered_value T>              constexpr T            abs(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns the modulus of its argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/abs.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_abs abs = {};
}
