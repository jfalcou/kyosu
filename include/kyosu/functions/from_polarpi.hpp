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
  struct from_polarpi_t : eve::strict_elementwise_callable<from_polarpi_t, Options>
  {
    template<concepts::real Z0, concepts::real Z1, concepts::cayley_dickson Z2>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_like_t<Z0, Z1, Z2>
    operator()(Z0 r, Z1 t, Z2 iz) const noexcept
    {
      return KYOSU_CALL(r, t, iz);
    }

    template<concepts::real Z0, concepts::real Z1>
    KYOSU_FORCEINLINE constexpr complexify_t<as_cayley_dickson_like_t<Z0, Z1>>
    operator()(Z0 r, Z1 t) const noexcept
    {
      return KYOSU_CALL(r, t);
    }

    KYOSU_CALLABLE_OBJECT(from_polarpi_t, from_polarpi_);
  };

  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var from_polarpi
  //!
  //! @brief Callable object computing a complex or a general Cayley-Dickson from a polar representation, with the argument
  //!        in \f$\pi\f$ multiples.
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
  //!     auto from_polarpi( T0 rho, T1 theta) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `rho`  : modulus.
  //!  `theta`: argument.
  //!
  //! **Return value**
  //!
  //!    the complex number `rho*exp_ipi(theta)`.
  //!
  //!  @note the entries constitue a proper polar representation if rho is non-negative, however the formula is used as is.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/from_polarpi.cpp}
  //================================================================================================
  inline constexpr auto from_polarpi = eve::functor<from_polarpi_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename C0, typename C1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto from_polarpi_(KYOSU_DELAY(), O const&, C0 rho, C1 theta) noexcept
  {
    auto r = eve::abs(rho);
    auto a = eve::if_else(eve::is_positive(rho), theta, eve::inc(theta));
    auto [s, c] = eve::sinpicospi(a);
    return complex(r*c, r*s);
  }
}
