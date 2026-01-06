//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include "kyosu/types/traits.hpp"
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct j_t : eve::constant_callable<j_t, Options>
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
      return typename result<T>::type{0,0,1,0};
    }

    template<concepts::cayley_dickson_like T>
    KYOSU_FORCEINLINE constexpr typename result<T>::type operator()(as<T> const& v) const
    {
      return KYOSU_CALL(v);
    }

    EVE_CALLABLE_OBJECT(j_t, j_);
  };

//======================================================================================================================
//! @addtogroup constants
//! @{
//!   @var j
//!   @brief Computes the complex number j i.e. quaternion(0, 0, 1, 0) in the chosen type.
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
//!      template<kyosu::concepts::cayley_dickson T> auto j(as<T> z) noexcept;
//!      template<eve::floating_ordered_value T>     auto j(as<T> z) noexcept;
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
//!  @godbolt{doc/j.cpp}
//======================================================================================================================
  inline constexpr auto j = eve::functor<j_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
