//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/sinpi.hpp>
#include <kyosu/functions/oneminus.hpp>
#include <kyosu/functions/exp.hpp>
#include <kyosu/functions/log.hpp>

namespace kyosu
{
  template<typename Options>
  struct log_gamma_t : eve::strict_elementwise_callable<log_gamma_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<kyosu::complexify_if_t<Options, Z>, K> operator()(
      Z const& z, K const& k) const noexcept
    requires(eve::same_lanes_or_scalar<Z, K>)
    {
      return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(log_gamma_t, log_gamma_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var log_gamma
  //!   @brief Computes \f$\log(\Gamma(z))\f$.
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
  //!     template<concepts::cayley_dickson_like Z> constexpr complexify_t<Z> log_gamma(Z z) noexcept;
  //!     template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log(T z eve::value n) noexcept;
  //!
  //!     // semantic modifyers
  //!     template<concepts::real Z> constexpr complexify_t<Z> log_gamma[real_only](Z z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z` : Value to process.
  //!
  //!   **Return value**
  //!
  //!   - A real typed input z is treated as if `complex(z)` was entered, unless the option real_only is used
  //!       in which case the  result will the same as to an `eve::log_gamma` call
  //!       implying a Nan result if the input is not greater than zero.
  //!  -  Returns \f$\Gamma(z)\f$.
  //!    - with two parameters use the nth branch of the logarithm.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Gamma Function](https://mathworld.wolfram.com/GammaFunction.html)
  //!   *  [Wikipedia: Gamma function](https://en.wikipedia.org/wiki/Gamma_function)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/log_gamma.cpp}
  //======================================================================================================================
  inline constexpr auto log_gamma = eve::functor<log_gamma_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O> constexpr auto log_gamma_(KYOSU_DELAY(), O const& o, Z a0) noexcept
  {
    if constexpr (O::contains(real_only) && concepts::real<Z>) return eve::log_gamma[o.drop(real_only)](a0);
    else if constexpr (concepts::real<Z>) return kyosu::log_gamma[o](complex(a0));
    else if constexpr (concepts::complex<Z>)
    {
      // 15 sig. digits for 0<=real(z)<=171
      // coeffs should sum to about g*g/2+23/24
      //
      using r_t = eve::element_type_t<as_real_type_t<Z>>;
      auto g = r_t(607) / r_t(128);
      // best results when 4<=g<=5
      constexpr int N = 15;
      std::array<r_t, N> c = {0.99999999999999709182,    57.156235665862923517,     -59.597960355475491248,
                              14.136097974741747174,     -0.49191381609762019978,   .33994649984811888699e-4,
                              .46523628927048575665e-4,  -.98374475304879564677e-4, .15808870322491248884e-3,
                              -.21026444172410488319e-3, .21743961811521264320e-3,  -.16431810653676389022e-3,
                              .84418223983852743293e-4,  -.26190838401581408670e-4, .36899182659531622704e-5};

      //Num Recipes used g=5 with 7 terms
      //for a less effective approximation

      auto negra0 = eve::is_negative(real(a0));
      auto z = if_else(negra0, -a0, a0);
      Z ss{};
      for (int pp = N - 1; pp >= 1; --pp) { ss += c[pp] * rec(z + eve::dec(pp)); }
      auto zg = z + g - eve::half(eve::as(g));
      auto lsq2pi = r_t(0.9189385332046727417803297);
      auto f = (lsq2pi + log(c[0] + ss)) - zg + (z - eve::half(eve::as<r_t>())) * log(zg);
      auto zer = eve::zero(eve::as(g));
      auto o = eve::one(eve::as(g));
      auto t = o + o;
      f = if_else(z == t || z == o, zer, f);
      //adjust for negative real parts
      if (eve::any(negra0))
      {
        auto lpi = r_t(1.14472988584940017414342735);
        auto reala0 = is_real(a0);
        f = kyosu::if_else(negra0, lpi - log(a0 * sinpi(-a0)) - f, f);
        f = kyosu::if_else(negra0 && reala0 && eve::is_flint(real(a0)),
                           complex(eve::nan(eve::as(g)), eve::inf(eve::as(g))), f);
      }
      return f;
    }
    else { return cayley_extend(log_gamma, a0); }
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log_gamma_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  requires(!O::contains(real_only))
  {
    if constexpr (kyosu::concepts::real<Z>) return log_gamma[o](complex(z));
    else if constexpr (kyosu::concepts::complex<Z>)
    {
      using e_t = eve::element_type_t<decltype(real(z))>;
      auto kk = eve::convert(k, as<e_t>());
      return log_gamma[o](z) + muli(kk * two_pi(as(kk)));
    }
    else { return _::cayley_extend(kyosu::log_gamma, z, k); }
  }

  template<concepts::real Z, eve::value... K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log_gamma_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), log_gamma(z, k...));
  }
}
