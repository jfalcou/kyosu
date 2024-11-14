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
  struct mi_t : eve::constant_callable<mi_t, Options>
  {
    template<typename T>
    static KYOSU_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      if constexpr(concepts::cayley_dickson<T>) return T{0,-1};
      else                                      return complex_t<eve::as_floating_point_t<T>>{0,-1};
    }

    template<typename T>
    requires(concepts::cayley_dickson<T>)
    KYOSU_FORCEINLINE constexpr T operator()(as<T> const& v) const { return KYOSU_CALL(v); }

    template<concepts::real T>
    KYOSU_FORCEINLINE constexpr auto operator()(as<T> const& v) const
    {
      return KYOSU_CALL(v);
    }

    EVE_CALLABLE_OBJECT(mi_t, i_);
  };

//======================================================================================================================
//! @addtogroup constants
//! @{
//!   @var mi
//!   @brief Computes the complex number \f$-i\f$ in the chosen type.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr as_complex_t<underlying_type_t<T>> mi(as<T> z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr as_complex_t<underlying_type_t<T>> mi(as<T> z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * always returns a complex scalar value mi such that real(mi) is null and imag(i) is -1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/mi.cpp}
//======================================================================================================================
  inline constexpr auto mi = eve::functor<mi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
