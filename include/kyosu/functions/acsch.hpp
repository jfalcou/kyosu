//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/asinh.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/details/branch_correct.hpp>

namespace kyosu
{
  template<typename Options> struct acsch_t : eve::elementwise_callable<acsch_t, Options>
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

    KYOSU_CALLABLE_OBJECT(acsch_t, acsch_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var acsch
  //!   @brief Computes the inverse hyperbolic cosecant of the argument.
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
  //!     //  regular calls
  //!     constexpr auto acsch(cayley_dickson_like z)               noexcept;
  //!     constexpr auto acsch(cayley_dickson_like z, eve::value k) noexcept;
  //!
  //!     // semantic modifyers
  //!     constexpr auto acsch[real_only](Real z)                   noexcept;
  //!   }
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!    - A real typed input z is treated as if `complex(z)` was entered, unless the option real_only is used
  //!      in which case the parameter must be a floating_value, and is equivalent to `eve::acsch`.
  //!    - For general cayley_dickson input, the call is equivalent to `asinh(rec(z))`.
  //!    - For two parameters returns the kth branch of `acsch`. If k is not a flint it is truncated before use.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/acsch.cpp}
  //======================================================================================================================
  inline constexpr auto acsch = eve::functor<acsch_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acsch_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr (O::contains(real_only)) return eve::acsch(z);
    else if constexpr (concepts::real<Z>) return kyosu::inject[real_only](eve::acsch(z));
    else return kyosu::asinh[o](kyosu::rec(z));
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acsch_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  requires(!O::contains(real_only))
  {
    using e_t = eve::element_type_t<decltype(real(z))>;
    auto kk = eve::convert(eve::trunc(k), eve::as<e_t>());
    return kyosu::acsch[o](z) + branch_correction<O>(kk);
  }

}
