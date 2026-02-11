//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/pow.hpp>
#include <kyosu/functions/is_unitary.hpp>
#include <kyosu/functions/signnz.hpp>
#include <kyosu/functions/conj.hpp>
#include <kyosu/details/decorators.hpp>
namespace kyosu
{
  template<typename Options> struct slerp_t : eve::strict_elementwise_callable<slerp_t, Options, assume_unitary_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, concepts::real Z2>
    requires(eve::same_lanes_or_scalar<Z0, Z1, Z2>)
    KYOSU_FORCEINLINE constexpr kyosu::as_cayley_dickson_like_t<complexify_t<Z0>, complexify_t<Z1>, Z2> operator()(
      Z0 const& c0, Z1 const& c1, Z2 const& c2) const noexcept
    {
      return KYOSU_CALL(c0, c1, c2);
    }

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
  //!     constexpr auto slerp(auto z0, auto z1, concepts::real t) noexcept;
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
  template<typename Z0, typename Z1, typename Z2, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto slerp_(KYOSU_DELAY(), O const&, Z0 z0, Z1 z1, Z2 z2) noexcept
  {
    if constexpr (concepts::real<Z0> && concepts::real<Z1>) return kyosu::slerp(complex(z0), complex(z1), z2);
    else if constexpr (!O::contains(assume_unitary))
    {
      z0 = kyosu::signnz(z0);
      z1 = kyosu::signnz(z1);
    }
    auto gez = eve::is_gez(real(kyosu::dot(z0, z1)));
    auto mix = kyosu::if_else(gez, z1, -z1);
    return z1 * kyosu::pow(kyosu::conj(z1) * mix, z2);
  }
}
