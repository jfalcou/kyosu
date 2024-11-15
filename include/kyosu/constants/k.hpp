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
  struct k_t : eve::constant_callable<k_t, Options>
  {
    template<typename T>
    static KYOSU_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      using e_t =  eve::underlying_type_t<T>;
      return quaternion(e_t(0),e_t(0),e_t(0),e_t(1));
    }

    template<typename T>
    requires(concepts::cayley_dickson<T>)
    KYOSU_FORCEINLINE constexpr auto operator()(as<T> const& v) const { return KYOSU_CALL(v); }

    template<concepts::real T>
    KYOSU_FORCEINLINE constexpr auto operator()(as<T> const& v) const
    {
      return KYOSU_CALL(v);
    }

    EVE_CALLABLE_OBJECT(k_t, k_);
  };

//======================================================================================================================
//! @addtogroup constants
//! @{
//!   @var k
//!   @brief Computes the complex number k i.e. quaternion(0, 0, 0, 1) in the chosen type.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto k(as<T> z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto k(as<T> z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * always returns a quaternion value `k` such that all parts are null except the `kpart` whose value is one.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/k.cpp}
//======================================================================================================================
  inline constexpr auto k = eve::functor<k_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
