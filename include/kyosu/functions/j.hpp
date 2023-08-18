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
  struct callable_j  : eve::constant
  {
    using deferred_callable_tag = void;
    using callable_tag_type     = callable_j;

    template<eve::floating_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, eve::as<T>) noexcept
    {
      using type = cayley_dickson<eve::element_type_t<T>,4>;
      return eve::as_wide_as_t<type,T>{type{0,0,1,0}};
    }

    template<concepts::cayley_dickson T>
    requires( dimension_v<T> >= 4)
    static KYOSU_FORCEINLINE auto deferred_call(auto, eve::as<T>) noexcept
    {
      using type = eve::element_type_t<T>;
      return T{type{0,0,1,0}};
    }

    template<eve::value T>
    KYOSU_FORCEINLINE auto operator()(eve::as<T> target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_j(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //====================================================================================================================
  //! @addtogroup constants
  //! @{
  //!   @var j
  //!   @brief Computes the constant \f$j\f$.
  //!
  //!   **Defined in Header:** `#include <kyosu/functions.hpp>`
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!     template<typename T>
  //!     constexpr T j(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters:** `x` - Constant type passed as a Type wrapper.
  //!
  //!   **Return value:** The imaginary `j` value.
  //!
  //!   @groupheader{Example}
  //!
  //!   @include doc/functions/j.cpp
  //! @}
  //====================================================================================================================
  inline constexpr tags::callable_j j = {};
}
