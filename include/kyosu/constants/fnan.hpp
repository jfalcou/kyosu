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
  struct fnan_t : eve::constant_callable<fnan_t, Options>
  {
    template<typename T>
    static KYOSU_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      using t_t = eve::as_floating_point_t<eve::underlying_type_t<T>>;

      if constexpr(concepts::cayley_dickson<T>)
      {
        T z;
        return  T{kumi::map([&z](auto const& e) {  return eve::nan(as(real(z))); }, z)};
        }
        else
          return complex_t<T>{eve::nan(as<t_t>()),eve::nan(as<t_t>())};
    }

    template<typename T>
    requires(concepts::cayley_dickson<T>)
    KYOSU_FORCEINLINE constexpr T operator()(as<T> const& v) const { return KYOSU_CALL(v); }

    template<concepts::real T>
    KYOSU_FORCEINLINE constexpr T operator()(as<T> const& v) const
    {
      return eve::nan(as(v));
    }

    EVE_CALLABLE_OBJECT(fnan_t, fnan_);
  };

//======================================================================================================================
//! @addtogroup constants
//! @{
//!   @var fnan
//!   @brief Computes the full nan constant such that all components of the chosen type are NaN.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr as_complex_t<eve::as_floating_point_t<T>> fnan(as<T> z) noexcept;
//!      template<kyosu::real T>     constexpr as_complex_t<eve::as_floating_point_t<T>> fnan(as<T> z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * always returns a cayley_dickson value such that all components are NaNs.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/fnan.cpp}
//======================================================================================================================
  inline constexpr auto fnan = eve::functor<fnan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
