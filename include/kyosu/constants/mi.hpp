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
    struct result : std::conditional<concepts::cayley_dickson<T>, T, as_cayley_dickson_n_t<2, T>>
    {};

    template<typename T>
    static KYOSU_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      return typename result<T>::type{0,-1};
    }

    template<concepts::cayley_dickson_like T>
    KYOSU_FORCEINLINE constexpr typename result<T>::type operator()(as<T> const& v) const
    {
      return KYOSU_CALL(v);
    }

    EVE_CALLABLE_OBJECT(mi_t, mi_);
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T mi(as<T> z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr complex_t<eve::as_floating_point_t<T>> mi(as<T> z) noexcept;
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
