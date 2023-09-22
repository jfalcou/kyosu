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
  struct callable_to_cylindrical : eve::elementwise
  {
    using callable_tag_type = callable_to_cylindrical;

    KYOSU_DEFERS_CALLABLE(to_cylindrical_);

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
    eve::unsupported_call<callable_to_cylindrical(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_cylindrical
  //!
  //! @brief Callable object computing the cylindrical coordinates from a quaternion.
  //!
  //!  This function is the reciprocal of from_cylindrical
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
  //!     auto to_cylindrical( auto q) const noexcept;
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
  //!  of the cylindrical parametrisation of \f$\mathbb{R}^4\f$ coordinates
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/to_cylindrical.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_to_cylindrical to_cylindrical = {};
}
