//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_polar.hpp>
#include <kyosu/functions/exp_i.hpp>

namespace kyosu
{
  template<typename Options>
  struct nthroot_t : eve::callable<nthroot_t, Options>
  {

    template<concepts::cayley_dickson_like Z, eve::integral_value N>
    KYOSU_FORCEINLINE constexpr auto//complexify_t<eve::as_wide_as_t<N, Z>>
    operator()(Z const& z, N const & n) const noexcept
    {
      return KYOSU_CALL(z, n);
    }

    template<concepts::cayley_dickson_like Z, eve::floating_value N>
    KYOSU_FORCEINLINE constexpr auto//complexify_t<eve::as_wide_as_t<N, Z>>
    operator()(Z const& z, N const & n) const noexcept
    {
      return KYOSU_CALL(z, n);
    }

    KYOSU_CALLABLE_OBJECT(nthroot_t, nthroot_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var nthroot
//!   @brief Computes the arc cosine of the argument in \f$\pi\f$ multiples.
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
//!     template<concepts::cayley_dickson_like Z> constexpr complexify_t<Z> nthroot(Z z) noexcept;
//!
//!     // semantic modifyers
//!     template<concepts::real Z> constexpr complexify_t<Z> nthroot[real_only](Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!  - A real input z is treated as if `complex(z)` was entered.
//!  - Returns radinpi(acos(z))
//!
//!  @groupheader{Example}
//!  @godbolt{doc/nthroot.cpp}
//======================================================================================================================
  inline constexpr auto nthroot = eve::functor<nthroot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::value N, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto nthroot_(KYOSU_DELAY(), O const& , Z z, N n) noexcept
  {
    if constexpr(eve::floating_value<Z>)
    {
      auto r = kyosu::complex(eve::nthroot(eve::abs(z), n));
      return if_else(eve::is_positive(z)
                    , r
                    , if_else(eve::is_odd(n), -r, r*kyosu::exp_ipi(rec(n)))
                    );
    }
    else if constexpr(concepts::complex<Z>)
    {

      auto rntn = [z](auto nn){
        auto [rho, theta] = kyosu::to_polar(z);
        auto realz = kyosu::is_real(z);
        auto posz  = kyosu::is_positive(z);
        auto rho_n = eve::nthroot(rho, fn);
        auto theta_n = theta*eve::rec(fn);
        rntn = rho_n*kyosu::exp_i(theta_n);
        return if_else(realz
                      , if_else(posz
                               , rho_n
                               , if_else(eve::is_odd(nn)
                                        , -rho_n
                                        , r*kyosu::exp_ipi(rec(nn))
                                        )
                               )
                      , rntn
                      );

      }
      if constexpr(eve::integral_simd_value<N>)
      {
        using r_t = eve::underlying_type_t<Z>;
        auto fn =  eve::convert(n, eve::as<r_t>());
        auto rho_n = eve::nthroot(rho, fn);
        auto theta_n = theta*eve::rec(fn);
        return rho_n*kyosu::exp_i(theta_n);
      }
      else if constexpr(eve::integral_scalar_value<N>)
      {
        auto rho_n = eve::nthroot(rho, n);
        auto theta_n = theta/n;
        return rho_n*kyosu::exp_i(theta_n);
      }
      else
      {
        auto rho_n = eve::nthroot(rho, n);
        auto theta_n = theta*eve::rec(n);
        return rho_n*kyosu::exp_i(theta_n);
      }
    }
    else  return  cayley_extend2(nthroot, z, n);
  }
}
