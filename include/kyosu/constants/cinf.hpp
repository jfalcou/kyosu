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
  struct cinf_t : eve::constant_callable<cinf_t, Options>
  {
    template<typename T>
    static KYOSU_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      using t_t = as_cayley_dickson_n_t<2, T>;
      using u_t = eve::underlying_type_t<t_t>;

      return t_t{eve::nan(as<u_t>()),eve::inf(as<u_t>())};
    }

    template<concepts::cayley_dickson_like T>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_n_t<2, T> operator()(as<T> const& v) const
    {
      return KYOSU_CALL(v);
    }

    EVE_CALLABLE_OBJECT(cinf_t, cinf_);
  };

//======================================================================================================================
//! @addtogroup constants
//! @{
//!   @var cinf
//!   @brief Computes the complex-infinite defined as \f$\textrm{NaN} + i\, \textrm{inf}\f$ in the chosen type.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr as_complex_t<eve::as_floating_point_t<T>> cinf(as<T> z) noexcept;
//!      template<kyosu::real T>     constexpr as_complex_t<eve::as_floating_point_t<T>> cinf(as<T> z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * always returns a cayley_dickson value such that real(i) is a NaN and imag(i) is \f$+\infty\f$ (the remaining parts being 0).
//!       This is meant to represent a quantity with infinite magnitude, but undetermined complex phase.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: complex infinity](https://reference.wolfram.com/language/ref/ComplexInfinity.html)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cinf.cpp}
//======================================================================================================================
  inline constexpr auto cinf = eve::functor<cinf_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
