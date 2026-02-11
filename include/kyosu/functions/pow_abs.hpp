//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/pow.hpp>
#include <kyosu/functions/if_else.hpp>

namespace kyosu
{
  template<typename Options> struct pow_abs_t : eve::callable<pow_abs_t, Options>
  {

    template<typename Z0, typename Z1> struct result
    {
      using type = decltype(kyosu::real(kyosu::pow(kyosu::abs(Z0()), Z1())));
    };

    template<kyosu::concepts::cayley_dickson_like Z0, kyosu::concepts::cayley_dickson Z1> struct result<Z0, Z1>
    {
      using type = decltype((kyosu::pow(kyosu::abs(Z0()), Z1())));
    };

    template<kyosu::concepts::cayley_dickson_like Z0, eve::integral_value Z1> struct result<Z0, Z1>
    {
      using r_t = decltype(eve::convert(Z1(), eve::as(eve::element_type_t<kyosu::as_real_type_t<Z0>>())));
      using type = decltype(kyosu::real(kyosu::pow(kyosu::abs(Z0()), r_t())));
    };

    //================================================================================

    template<typename Z0, typename Z1> using result_t = typename result<Z0, Z1>::type;

    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson Z1>
    requires(!eve::integral_value<Z1>)
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 z0, Z1 z1) const noexcept -> result_t<Z0, Z1>
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::cayley_dickson_like Z0, eve::floating_value Z1>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 z0, Z1 z1) const noexcept -> result_t<Z0, Z1>
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::cayley_dickson_like Z0, eve::integral_value Z1>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 z0, Z1 z1) const noexcept -> result_t<Z0, Z1>
    {
      return KYOSU_CALL(z0, z1);
    }

    KYOSU_CALLABLE_OBJECT(pow_abs_t, pow_abs_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var pow_abs
  //!   @brief Computes the pow_abs operation \f$|x|^y\f$.
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
  //!     constexpr auto pow_abs(auto z0, auto z1) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z0`, `z1`: Values to process.
  //!
  //!   **Return value**
  //!
  //!      the call is semantically equivalent to `kyosu::exp(log_abs(z0)*z1)` In particular if z1 is a floating value the
  //!      result is a floating value, which is not the case of kyosu::pow(abs(z0), z1);
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/pow_abs.cpp}
  //======================================================================================================================
  inline constexpr auto pow_abs = eve::functor<pow_abs_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{

  template<typename Z0, typename Z1, eve::callable_options O>
  constexpr auto pow_abs_(KYOSU_DELAY(), O const&, Z0 z0, Z1 z1) noexcept
  {
    if constexpr (eve::integral_simd_value<Z1>)
    {
      using r_t = kyosu::as_real_type_t<eve::as_wide_as_t<Z0, Z1>>;
      if constexpr (eve::unsigned_value<Z1>)
      {
        r_t base(eve::abs(z0));
        auto expo = z1;

        auto result = eve::one(eve::as<r_t>());
        while (eve::any(eve::is_nez(expo)))
        {
          auto fac = eve::if_else(eve::is_odd(expo), base, eve::one);
          result *= fac;
          expo = (expo >> 1);
          base = eve::sqr(base);
        }
        return result;
      }
      else
      {
        using u_t = eve::as_integer_t<Z1, unsigned>;
        r_t tmp = kyosu::pow_abs(z0, eve::bit_cast(eve::abs(z1), eve::as<u_t>()));
        return eve::if_else(eve::is_ltz(z1), eve::rec[eve::pedantic](tmp), tmp);
      }
    }
    else if constexpr (eve::integral_scalar_value<Z1>) { return eve::pow(kyosu::abs(z0), z1); }
    else if constexpr (concepts::real<Z1>) return eve::pow(kyosu::abs(z0), z1);
    else return kyosu::pow(kyosu::abs(z0), z1);
  }
}
