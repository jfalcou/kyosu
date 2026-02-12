//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/hypergeometric.hpp>
#include <kyosu/functions/acos.hpp>
#include <kyosu/functions/cos.hpp>

namespace kyosu
{
  template<typename Options>
  struct legendre_t : eve::strict_elementwise_callable<legendre_t, Options, eve::successor_option>
  {
    template<concepts::real N, concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto operator()(N nn, Z zz) const noexcept -> decltype(nn + zz)
    {
      using r_t = decltype(nn + zz);
      using u_t = eve::underlying_type_t<r_t>;
      auto n = r_t(nn);
      auto z = r_t(zz);
      auto r =
        kyosu::hypergeometric(oneminus(z) * eve::half(eve::as<u_t>()), kumi::tuple{-n, n + 1}, kumi::tuple{u_t(1.0)});
      return if_else(is_real(z), complex(real(r)), r);
    }

    template<concepts::real N, concepts::real Z>
    KYOSU_FORCEINLINE constexpr auto operator()(N n, Z z) const noexcept -> decltype(n + complex(z))
    {
      return (*this)(n, complex(z));
    }

    // Recurrence relation for Legendre polynomials:
    template<concepts::cayley_dickson Z, concepts::cayley_dickson T, concepts::real N>
    KYOSU_FORCEINLINE constexpr auto operator()(N n, Z z, T pn, T pnm1) const noexcept -> decltype(z + pn)
    {
      auto np1 = kyosu::inc(n);
      return ((n + np1) * z * pn - n * pnm1) / np1;
    }

    template<concepts::real Z, concepts::cayley_dickson T, concepts::real N>
    KYOSU_FORCEINLINE constexpr auto operator()(N n, Z z, T pn, T pnm1) const noexcept -> decltype(z + pn)
    {
      return (*this)(n, complex(z), pn, pnm1);
    }
  };

  //================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var legendre
  //!   @brief Computes the value of the Legendre and associated
  //!   Legendre functions of order `n` ( and `m`) at `x`:
  //!
  //!   For positive integer `n` the standard legendre functions are polynomials:
  //!    * The Legendre polynomial of order n is given by \f$\displaystyle \mbox{L}_{n}(x)
  //!      = \frac{e^x}{n!}\frac{d^n}{dx^n}(x^ne^{-x})\f$.
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
  //!   namespace eve
  //!   {
  //!      // Regular overload
  //!      auto constexpr legendre(kyosu::concepts::real auto n, kyosu::concepts::cayley_dickson auto z) noexcept; // 1
  //!      auto constexpr legendre(kyosu::concepts::real auto n, kyosu::concepts::real auto z)           noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto legendre[conditional_expr auto c](/* any previous overload */)                 noexcept; // 2
  //!      constexpr auto legendre[logical_value auto m](/* any previous overload */)                    noexcept; // 2
  //!
  //!      // Semantic options
  //!      constexpr auto legendre[successor](integral_value auto n,
  //!                                         kyosu::concepts::cayley_dickson auto z,
  //!                                         kyosu::concepts::cayley_dickson auto pn,
  //!                                         kyosu::concepts::cayley_dickson auto pnm1)                  noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`: real positive argument.
  //!     * `z`: cayley_dickson or real argument
  //!     * `pn`, `pnm1`: cayley_dickson arguments
  //!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
  //!
  //!    **Return value**
  //!
  //!      1. The value of the Legendre function  of order `n` at `z` is returned.
  //!      2. [The operation is performed conditionnaly](@ref conditional).
  //!      3. The `successor` option implements the three term recurrence relation for the
  //!         (associated) Legendre functions, \f$\displaystyle \mbox{P}_{l+1} =
  //!         \left((2l+1)\mbox{P}_{l}(x)-l\mbox{P}_{l-1}(x)\right)/(l+1)\f$.
  //!
  //!  @groupheader{External references}
  //!   *  [DLMF: Classical Orthogonal Polynomials](https://dlmf.nist.gov/18.3)
  //!   *  [C++ standard reference: legendre](https://en.cppreference.com/w/cpp/numeric/special_functions/legendre)
  //!   *  [Wolfram MathWorld: Legendre Polynomial](https://mathworld.wolfram.com/LegendrePolynomial.html)
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/legendre.cpp}
  //================================================================================================
  inline constexpr auto legendre = eve::functor<legendre_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}
