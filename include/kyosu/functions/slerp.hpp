//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/pow.hpp>
#include <kyosu/functions/is_unitary.hpp>
#include <kyosu/functions/signnz.hpp>
#include <kyosu/functions/conj.hpp>
#include <kyosu/details/decorators.hpp>
namespace kyosu
{
  template<typename Options>
  struct slerp_t : eve::strict_elementwise_callable<slerp_t, Options, assume_unitary_option>
  {
    template<typename Z0, typename Z1, typename Z2>
    requires((concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)&& concepts::real<Z2>)
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& z0, Z1 const & z1, Z2 const & z2) const noexcept -> decltype(z0+z1+z2)
    { return KYOSU_CALL(z0,z1,z2); }

    template<concepts::real V0, concepts::real V1, concepts::real V2>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1, V2 v2) const noexcept -> decltype(complex(v0)+complex(v1)+v2)
    { return (*this)(complex(v0),complex(v1),v2); }

    KYOSU_CALLABLE_OBJECT(slerp_t, slerp_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var slerp
//!   @brief  Computes the  spherical interpolation between unitary quaternions.
//!
//!   @groupheader{Header file}
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
//!     constexpr auto slerp(auto z0, auto z1, floating_ordered_value t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: unitary quaternions to process.
//!     * `t`: floating value interpolation coefficient.
//!
//!   **Return value**
//!
//!    The value of the spherical interpolation (or extrapolation)  between `z0` and `z1` is returned.
//!
//!    @note The function does not assume that `z0` and  `z1` are unitary. The option `assume_unitary` allows
//!          to avoid unecessary normalizations if `z0` and  are already normalized.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/slerp.cpp}
//======================================================================================================================
  inline constexpr auto slerp = eve::functor<slerp_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z1, typename Z2, typename T, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto slerp_(KYOSU_DELAY(), O const&, Z1 z1, Z2 z2, T t) noexcept
  {
    if constexpr(!O::contains(assume_unitary))
    {
      z1 = signnz(z1);
      z2 = signnz(z2);
    }
    auto gez = eve::is_gez(real(kyosu::dot(z1, z2)));
    auto mix = kyosu::if_else(gez, z2, -z2);
    return z1*kyosu::pow(kyosu::conj(z1)*mix, t);
  }
}
