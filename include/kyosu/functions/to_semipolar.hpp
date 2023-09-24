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
  struct callable_to_semipolar : eve::elementwise
  {
    using callable_tag_type = callable_to_semipolar;

    KYOSU_DEFERS_CALLABLE(to_semipolar_);

    template<eve::ordered_value V>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & v) noexcept
    {
      auto z = eve::zero(eve::as(v));
      return kumi::tuple{eve::abs(v), eve::arg(v), z, z};
    }

    template<typename T0>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0))
    {
      return eve::tag_invoke(*this, target0);
    }

    template<typename... T>
    eve::unsupported_call<callable_to_semipolar(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_semipolar
  //!
  //! @brief Callable object computing the semipolar coordinates from a quaternion.
  //!
  //!  This function is the reciprocal of from_semipolar
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
  //!     auto to_semipolar( auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q` : quaternion
  //!
  //! **Return value**
  //!
  //!  a tuple containing in this order `rho1`, 'theta1', `h1` 'h2':  the components
  //!  of the semipolar parametrisation of \f$\mathbb{R}^4\f$ coordinates
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/to_semipolar.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_to_semipolar to_semipolar = {};
}
