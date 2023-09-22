//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright : KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu::tags
{
  struct callable_to_polar : eve::elementwise
  {
    using callable_tag_type = callable_to_polar;

    KYOSU_DEFERS_CALLABLE(to_polar_);

    template<eve::floating_ordered_value V>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & v) noexcept
    {
      auto z = eve::zero(eve::as(v));
      return kumi::tuple{eve::abs(v), eve::arg(v)};
    }

    template<typename T0>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0))
    {
      return eve::tag_invoke(*this, target0);
    }

    template<typename... T>
    eve::unsupported_call<callable_to_polar(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var to_polar
  //!
  //! @brief Callable object computing the polar coordinates from a complex.
  //!
  //!  This function is the reciprocal of from_polar
  //!
  //! **Defined in header**
  //!
  //!   @code
  //!   #include eve/module/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!     auto to_polar( auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q` : quaternion
  //!
  //! **Return value**
  //!
  //!  a tuple containing in this order `rho`, 'theta':  the modulus
  //!  and  the argument in radian of the complex input
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/regular/to_polar.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_to_polar to_polar = {};
}
