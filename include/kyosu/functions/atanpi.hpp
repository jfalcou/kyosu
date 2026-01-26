//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/atan.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct atanpi_t : eve::strict_elementwise_callable<atanpi_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr  complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr  eve::as_wide_as_t<complexify_if_t<Options, Z>, K>
    operator()(Z const& z, K const & k) const noexcept
    {
     return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(atanpi_t, atanpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var atanpi
//!   @brief Computes the arc tangent of the argument in \f$\pi\f$ multiples.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!     //  regular call
//!     constexpr auto atanpi(cayley_dickson_like z)                noexcept;
//!     constexpr auto atanpi(cayley_dickson_like z, eve::value k)  noexcept;
//!
//!     // semantic modifyers
//!      constexpr Z atanpi[real_only](Real z)                      noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!    - A real typed input `z` is treated as if `complex(z)` was entered unless the option real_only is used
//!     in which case the parameter must be a floating_value and the result will the same as a call to `eve::atan`,
//!    - Returns `radinpi(atan(z))`
//!    - For two parameters returns the kth branch of `atanpi`. If k is not a flint it is truncated before use.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/atanpi.cpp}
//======================================================================================================================
  inline constexpr auto atanpi = eve::functor<atanpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto atanpi_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  {
    using e_t =  eve::element_type_t<decltype(real(z))>;
    auto kk = eve::convert(eve::trunc(k), eve::as<e_t>());
    return kyosu::atanpi[o](z)+2*kk;
  }

  template<concepts::cayley_dickson_like Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto atanpi_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    return radinpi(kyosu::atan[o](z));
  }

  template<concepts::real Z, eve::value ...K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto atanpi_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), atanpi(z, k...));
  }
}
