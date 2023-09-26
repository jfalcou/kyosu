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
  //!      template<eve::ordered_value T>              constexpr auto arg(T z) noexcept;  //1
  //!      template<kyosu::concepts::complex T>        constexpr auto atan(T z) noexcept;  //2
  //!      template<kyosu::concepts::cayley_dickson T> constexpr auto argy(T z) noexcept;  //3
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q` : cayley dickson value
  //!
  //! **Return value**
  //!
  //!    1. a tuple containing `rho`, 'theta':  the absolute value
  //!      and  the argument in radian of the real input (\f$0\f$ or\f$\pi\f$).
  //!
  //!    2. a tuple containing `rho`, 'theta':  the modulus
  //!      and  the argument in radian of the complex  input.
  //!
  //!    3. a tuple containing `rho`, 'theta'  the modulus
  //!      and  the argument in radian of the cayley input and a square root of -1 iz such
  //!       that `z = rho*exp(iz*theta). The leading coefficient of ìz` is chosen non-negative.`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/to_polar.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_to_polar to_polar = {};
}
