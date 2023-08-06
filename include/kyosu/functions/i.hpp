//======================================================================================================================
/*
  Kyosu - Complex Math Made Easy
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_i  : eve::constant
  {
    using deferred_callable_tag = void;
    using callable_tag_type     = callable_i;

    template<eve::floating_value T>
    static EVE_FORCEINLINE auto deferred_call(auto, eve::as<T>) noexcept
    {
      using type = caley_dickinson<eve::element_type_t<T>,2>;
      return eve::as_wide_as_t<type,T>{type{0,1}};
    }

    template<concepts::caley_dickinson T>
    static EVE_FORCEINLINE auto deferred_call(auto, eve::as<T>) noexcept
    {
      using type = eve::element_type_t<T>;
      return T{type{0,1}};
    }

    template<eve::value T>
    EVE_FORCEINLINE auto operator()(eve::as<T> target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_i(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, EVE_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //====================================================================================================================
  //! @addtogroup constants
  //! @{
  //!   @var j
  //!   @brief Computes the constant \f$i\f$.
  //!
  //!   **Defined in Header:** `#include <kyosu/functions.hpp>`
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!     template<typename T>
  //!     constexpr T i(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters:** `x` - Constant type passed as a [Type wrapper](@ref eve::as).
  //!
  //!   **Return value:** The imaginary `i` value.
  //!
  //!   @groupheader{Supported decorators}
  //!
  //!   * @ref conditional : Apply masks to the generated constant.
  //!
  //!   @groupheader{Example}
  //!
  //!   @include doc/functions/i.cpp
  //! @}
  //====================================================================================================================
  inline constexpr tags::callable_i i = {};
}
