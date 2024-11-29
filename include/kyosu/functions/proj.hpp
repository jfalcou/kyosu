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
  struct proj_t : eve::elementwise_callable<proj_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return if_else(eve::is_infinite(v), eve::inf(as(v)), v); }

    KYOSU_CALLABLE_OBJECT(proj_t, proj_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var proj
//!   @brief Callable object computing proj(x), the projection of the cayley_dickson number
//!   z onto the (hyper) Riemann sphere
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T proj(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T proj(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to project.
//!
//!   **Return value**
//!
//!     *  For most z, proj(z)==z, but all infinities, even the numbers where one component
//!        is infinite and the other is NaN, become positive real\n
//!        infinity, (inf, 0...) or (inf, -0...).\n
//!        The sign of the pure (zero) components are the signs of the components of pure(z).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/proj.cpp}
//======================================================================================================================
  inline constexpr auto proj = eve::functor<proj_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto proj_(KYOSU_DELAY(), O const&, C c) noexcept
  {
    using real_t = eve::as<as_real_type_t<C>>;
    if constexpr (kyosu::concepts::complex<C>)
      return if_else(is_infinite(c)
                    , complex(eve::inf(real_t{}), eve::copysign(eve::zero(real_t{}), imag(c)))
                    , c);
    else
    {
      auto isinf = is_infinite(c);
      auto tmp = eve::if_else(isinf, eve::inf(real_t{}), real(c));
      auto setpure = [isinf](auto & x){
        x = eve::if_else(isinf, eve::copysign(eve::zero(real_t{}), x), x);
      };
      kumi::for_each(setpure,  c);
      real(c) = tmp;
      return c;
    }
  }
}
