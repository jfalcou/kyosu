//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct from_polar_t : eve::strict_elementwise_callable<from_polar_t, Options>
  {
    template<concepts::real Z0, concepts::real Z1, concepts::cayley_dickson Z2>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 r, Z1 t, Z2 iz) const noexcept -> decltype(r+t+iz)
    {
      return KYOSU_CALL(r, t, iz);
    }

    template<concepts::real Z0, concepts::real Z1>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 r, Z1 t) const noexcept -> complex_t<decltype(r+t)>
    {
      return KYOSU_CALL(r, t);
    }

    KYOSU_CALLABLE_OBJECT(from_polar_t, from_polar_);
  };

  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var from_polar
  //!
  //! @brief Callable object computing a complex or a general Cayley-Dickson from a polar representation.
  //!
  //!  This function is the reciprocal of to_polar
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   #include kyosu/quaternion.hpp>`
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
  //!  `rho`  : modulus.
  //!
  //!  `theta`: argument.
  //!
  //!  `iz`   : unitary cayley dickson value.
  //!
  //! **Return value**
  //!
  //!    1. the complex number `rho*exp(i*theta)`.
  //!    2. the cayley_dickson value `rho*exp(iz*theta)`.
  //!
  //!  @note the entries constitue a proper polar representation if rho is non-negative and if iz present
  //!        it must be pure unitary with non-negative jpart. However the formula is used as is.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/from_polar.cpp}
  //================================================================================================
  inline constexpr auto from_polar = eve::functor<from_polar_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename C0, typename C1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto from_polar_(KYOSU_DELAY(), O const&, C0 rho, C1 theta) noexcept
  {
    auto r = eve::abs(rho);
    auto a = eve::if_else(eve::is_positive(rho), theta, eve::pi(eve::as(theta))+theta);
    auto [s, c] = eve::sincos(a);
    return complex(r*c, r*s);
  }

  template<typename C0, typename C1, typename C2, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto from_polar_(KYOSU_DELAY(), O const&, C0 rho, C1 theta, C2 iz) noexcept
  {
    return rho*kyosu::exp(theta*iz);
  }
}
