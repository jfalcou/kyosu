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
#include <kyosu/functions/asin.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options> struct asinpi_t : eve::strict_elementwise_callable<asinpi_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<complexify_if_t<Options, Z>, K> operator()(Z const& z,
                                                                                             K const& k) const noexcept
    {
      return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(asinpi_t, asinpi_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var asinpi
  //!   @brief Computes the arc sine of the argument in \f$\pi\f$ multiples.
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
  //!     constexpr auto asinpi(Z z)                               noexcept;
  //!     constexpr auto asin(ayley_dickson_like z, eve::value k)  noexcept;
  //!
  //!     // semantic modifyers
  //!     constexpr auto asinpi[real_only](Real z)                 noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //! **Return value**
  //!
  //!   - A real typed input `z` is treated as if `complex(z)` was entered unless the option real_only is used
  //!     in which case the parameter must be a floating_value and the result will the same as a call to `eve::asinpi`,
  //!     implying a `Nan` result if the theoretical result is not real.
  //!   - returns `radinpi(asin(z))`
  //!   - for two parameters returns the kth branch of `asinpi`. If k is not a flint, it is truncated before use.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/asinpi.cpp}
  //======================================================================================================================
  inline constexpr auto asinpi = eve::functor<asinpi_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asinpi_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    return radinpi(kyosu::asin[o](z));
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asinpi_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  requires(!O::contains(real_only))
  {
    using e_t = eve::element_type_t<decltype(real(z))>;
    auto kk = eve::convert(eve::trunc(k), eve::as<e_t>());
    return kyosu::asinpi[o](z) + 2 * kk;
  }

  template<concepts::real Z, eve::value... K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asinpi_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), asinpi(z, k...));
  }
}
