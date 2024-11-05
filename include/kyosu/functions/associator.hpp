//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct associator_t : eve::strict_elementwise_callable<associator_t, Options, eve::pedantic_option>
  {
    template<typename Z0, typename Z1, typename Z2>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1> ||concepts::cayley_dickson<Z2>)
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1, Z2 const & z2) const noexcept -> decltype(z0+z1+z2)
    {
      return KYOSU_CALL(z0,z1,z2);
    }

    template<concepts::real V0, concepts::real V1, concepts::real V2>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1, V2 v2) const noexcept -> decltype(v0+v1+v2)
    { return KYOSU_CALL(v0,v1,v2); }

    KYOSU_CALLABLE_OBJECT(associator_t, associator_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var associator
//!   @brief Computes the associator of the three parameters.
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
//!     Regular call
//!     constexpr auto associator(auto z0, auto z1, auto z2) noexcept;
//!
//!     Semantic modifyier
//!     constexpr auto associator[pedantic](auto z0, auto z1, auto z2) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`, z2`: Values to process. Can be a mix of complex and real floating values and complex values.
//!
//!   **Return value**
//!
//!     1.  Returns the difference z0*(z1*z2)-(z0*z1)*z2. (always exactly zero up to quaternion)
//!     2.  Returns the difference z0*(z1*z2)-(z0*z1)*z2. (up to quaternions, non zero result is merely the floating point associativity default)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/associator.cpp}
//======================================================================================================================
  inline constexpr auto associator = eve::functor<associator_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{

  template<typename C0, typename C1, typename C2, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto associator_(KYOSU_DELAY(), O const&
                                              , C0 c0, C1 c1, C2 c2) noexcept
  {
    if constexpr(O::contains(eve::pedantic))
       return (c0*c1)*c2 - c0*(c1*c2);
    else
    {
      constexpr size_t dC0 = dimension_v<C0>;
      constexpr size_t dC1 = dimension_v<C1>;
      constexpr size_t dC2 = dimension_v<C2>;
      if constexpr((dC0 < 8 && dC1 < 8 && dC2 < 8) || (dC0 == 1 || dC1 == 1 || dC2 == 1))
      {
        return zero(as<decltype(c0+c1+c2)>());
      }
      else
      {
        return (c0*c1)*c2 - c0*(c1*c2);
      }
    }
  }
}
