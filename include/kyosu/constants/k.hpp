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
    struct result : std::conditional<(concepts::cayley_dickson<T> && dimension_v<T> > 2)
                                    , T
                                    , as_cayley_dickson_n_t<4, T>
                                    >
    {};

    template<typename T>
    static KYOSU_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      return typename result<T>::type{0,0,0,1};
    }

    template<concepts::cayley_dickson_like T>
    KYOSU_FORCEINLINE constexpr typename result<T>::type operator()(as<T> const& v) const
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
//!     * always returns a cayley-dickson which has dimension at least 4 and  value `j` such
//!       that all parts are null except the `jpart` whose value is one.
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
