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
    struct result : std::conditional<concepts::cayley_dickson<T>, T, as_cayley_dickson_n_t<2, T>>
    {};

    template<typename T>
    static KYOSU_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      return typename result<T>::type{0,1};
    }

    template<concepts::cayley_dickson_like T>
    KYOSU_FORCEINLINE constexpr typename result<T>::type operator()(as<T> const& v) const
    {
      return KYOSU_CALL(v);
    }

    EVE_CALLABLE_OBJECT(i_t, i_);
  };

//======================================================================================================================
//! @addtogroup constants
//! @{
//!   @var i
//!   @brief Computes the complex number \f$i\f$ in the chosen type.
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
//!      template<kyosu::real T>                     constexpr complex_t<eve::as_floating_point_t<T>>  i(as<T> t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!   * `t` :  Type wrapper instance embedding the type of the constant.
//!
//!   **Return value**
//!
//!   A kyosu::complex value `z` such that `real(z)` is 0 and `imag(z)` is 1.
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
