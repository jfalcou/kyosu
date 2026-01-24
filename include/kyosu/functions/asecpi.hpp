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
#include <kyosu/functions/asec.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct asecpi_t : eve::strict_elementwise_callable<asecpi_t, Options, real_only_option>
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

    KYOSU_CALLABLE_OBJECT(asecpi_t, asecpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asecpi
//!   @brief Computes the arc secant of the argument in \f$\pi\f$ multiples.
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
//!     constexpr auto asecpi(cayley_dickson_like z)               noexcept;
//!     constexpr auto asecpi(cayley_dickson_like z, eve::value k) noexcept;
//!
//!     // semantic modifyers
//!     constexpr auto secpi[real_only](Real z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   - A real typed input z is treated as if `complex(z)` was entered unless the option real_only is used
//!     in which case the parameter must be a floating_value,  the real part of the result will the same as an eve::asecpi
//!     implying a Nan result if the result is not real.
//!   - For general cayley_dickson input, returns `radinpi(asec(z))`
//!   - for two parameters returns the kth branch of `asecpi`. If k is not a flint, it is truncated before use.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asecpi.cpp}
//======================================================================================================================
  inline constexpr auto asecpi = eve::functor<asecpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asecpi_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    return  radinpi(kyosu::asec[o](z));
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asecpi_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  requires(!O::contains(real_only))
  {
    using e_t =  eve::element_type_t<decltype(real(z))>;
    auto kk = eve::convert(eve::trunc(k), eve::as<e_t>());
    return kyosu::asecpi[o](z)+2*kk;
  }

  template<concepts::real Z, eve::value ...K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asecpi_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), asecpi(z, k...));
  }

}
