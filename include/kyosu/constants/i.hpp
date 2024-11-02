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
  struct i_t : eve::constant_callable<i_t, Options>
  {
    template<typename T>
    static KYOSU_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      if constexpr(concepts::cayley_dickson<T>) return T{0,1};
      else                                      return complex_t<eve::as_floating_point_t<T>>{0,1};
    }

    template<typename T>
    requires(concepts::cayley_dickson<T>)
    KYOSU_FORCEINLINE constexpr T operator()(as<T> const& v) const { return KYOSU_CALL(v); }

    template<concepts::real T>
    KYOSU_FORCEINLINE constexpr auto operator()(as<T> const& v) const
    {
      return KYOSU_CALL(v);
    }

    EVE_CALLABLE_OBJECT(i_t, i_);
  };

//======================================================================================================================
//! @addtogroup constants
//! @{
//!   @var i
//!   @brief Computes the complex number \f$i$\f in the chosen type.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <kyosu/constants.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!      template<kyosu::concepts::cayley_dickson T> constexpr T  i(as<T> t) noexcept;
//!      template<kyosu::real T>                     constexpr as_complex_t<eve::as_floating_point_t<T>>  i(as<T> t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!   * `t` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!   **Return value**
//!
//!   A kyosu::complex value `z` such that kyosu::real(z) is 0 and kyosu::imag(z) is 1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/i.cpp}
//======================================================================================================================
  inline constexpr auto i = eve::functor<i_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
