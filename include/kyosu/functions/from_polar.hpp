//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright : KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/functions/to_quaternion.hpp>

namespace kyosu::tags
{
  struct callable_from_polar : eve::elementwise
  {
    using callable_tag_type = callable_from_polar;

    KYOSU_DEFERS_CALLABLE(from_polar_);

    template<eve::floating_ordered_value V, eve::floating_ordered_value U>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & v
                                               , U const & u) noexcept
    {
      auto r = eve::abs(v);
      auto a = eve::if_else(eve::is_positive(v), u, eve::pi(eve::as(u))+u);
      auto [s, c] = eve::sincos(a);
      return complex(r*c, r*s);
    }

    template<typename T0, typename T1>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0, T1 const& target1
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename T0, typename T1, typename T2>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0, T1 const& target1, T2 const& target2
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, target2))
    {
      return eve::tag_invoke(*this, target0, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_from_polar(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var from_polar
  //!
  //! @brief Callable object computing a complex from its polar coordinates.
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
  //!    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1>,
  //!     auto from_polar( T0 rho, T1 theta) const noexcept;                   // 1
  //!    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1, kyosu::concepts::cayley_dickson C>,
  //!     auto from_polar( T0 rho, T1 theta, C iz) const noexcept;             // 2
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `rho`   : modulus.
  //!  `theta` : argument.
  //!  `iz'    : unitary cayley dickson value.
  //!
  //! **Return value**
  //!
  //!    1. the complex number `rho*exp(i*theta)`.
  //!    2. the cayley_dickson value `rho*exp(iz*theta)`.
  //!
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/from_polar.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_from_polar from_polar = {};
}
