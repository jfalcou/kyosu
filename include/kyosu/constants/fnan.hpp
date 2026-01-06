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
    struct result : std::conditional<concepts::cayley_dickson<T>, T, as_cayley_dickson_n_t<2, T>>
    {};

    template<typename T>
    static KYOSU_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      using t_t = typename result<T>::type;
      using u_t = eve::underlying_type_t<t_t>;

      return t_t{ kumi::fill<kumi::size_v<eve::element_type_t<t_t>>>(eve::nan(as<u_t>()))};
    }

    template<concepts::cayley_dickson_like T>
    KYOSU_FORCEINLINE constexpr typename result<T>::type operator()(as<T> const& v) const
    {
      return KYOSU_CALL(v);
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
