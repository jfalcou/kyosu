//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/abs.hpp>
#include <kyosu/functions/maxabs.hpp>
#include <kyosu/details/decorators.hpp>

namespace kyosu
{
  template<typename Options>
  struct linfnorm_t : eve::strict_elementwise_callable<linfnorm_t, Options, kyosu::flat_option>
  {

    template<concepts::cayley_dickson_like Z1, concepts::cayley_dickson_like... Zs>
    requires(eve::same_lanes_or_scalar<Z1, Zs...>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z1 const & z1, Zs const & ...zs) const noexcept// -> decltype(eve::maxabs(real(z1), real(zs)...))
    {
      return KYOSU_CALL(z1, zs...);
    }

    KYOSU_CALLABLE_OBJECT(linfnorm_t, linfnorm_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var linfnorm
//!   @brief Callable object computing the linfnorm operation \f$ \max_{i = 0}^n |x_i| \f$.
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
//!      //regular call
//!      template<typename T, typename ... Ts> auto linfnorm(T z,Ts ... zs ) const       noexcept //1
//!
//!       Semantic modifyier
//!      template<typename T, typename ... Ts> auto linfnorm[flat](T z,Ts ... zs ) const noexcept //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zs...`: real or Cayley-dickson values to process.
//!
//!   **Return value**
//!
//!     1. Returns \f$ \max_{i = 0}^n |x_i| \f$. This is equivalent to a call to [lpnorm](@ref lpnorm) with `p` being `inf`
//!     2. the `flat` option computes the infinite norm of the tuple of real and other parts of the inputs. For instance for
//!        complex entries:  \f$ \max_{i = 0}^n \max(|\real(x_i)|, |\ipart(x_i)|)\f$.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Error Function](https://en.wikipedia.org/wiki/Linf_space)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/linfnorm.cpp}
//======================================================================================================================
  inline constexpr auto linfnorm = eve::functor<linfnorm_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
namespace kyosu::_
{
  template<eve::callable_options O, typename Z1, typename... Zs>
  EVE_FORCEINLINE constexpr auto linfnorm_(KYOSU_DELAY(), O const&, Z1 const& z1, Zs const& ... zs) noexcept
  {
    if constexpr(concepts::real<Z1> && (... && concepts::real<Zs>))
    {
      if constexpr(sizeof...(zs) == 0)
        return eve::abs(z1);
      else
        return eve::maxabs(z1,zs...);
    }
    else if constexpr(O::contains(kyosu::flat))
    {
      if constexpr(sizeof...(zs) == 0)
        return eve::maxabs(kyosu::real(z1), kyosu::imag(z1));
      else
        return eve::maxabs(kumi::cat(kumi::make_tuple(kyosu::real(z1), kyosu::real(zs)...),
                                     kumi::make_tuple(kyosu::imag(z1), kyosu::imag(zs)...)));
    }
    else
    {
      if constexpr(sizeof...(zs) == 0)
        return kyosu::abs(z1);
      else
        return kyosu::maxabs(z1, zs...);
    }
  }
}
