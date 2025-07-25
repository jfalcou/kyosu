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
#include <kyosu/functions/oneminus.hpp>
#include <kyosu/functions/pow.hpp>
#include <kyosu/functions/tgamma.hpp>
#include <kyosu/functions/dec.hpp>
#include <kyosu/functions/exp2.hpp>

namespace kyosu
{
  template<typename Options>
  struct deta_t : eve::strict_elementwise_callable<deta_t, Options>
  {
    template<concepts::cayley_dickson_like Z, eve::unsigned_scalar_value K>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(K k, Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(k, complex(z));
      else
        return KYOSU_CALL(k, z);
    }

    KYOSU_CALLABLE_OBJECT(deta_t, deta_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var deta
//!   @brief Computes the Dirichlet sums \f$ \displaystyle \sum_{n = 0}^\infty \frac{(-1)^n}{(kn+1)^z}\f$.
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
//!      template<concepts::cayley_dickson_like Z> complexify_t<Z> constexpr deta(unsigned_scalar_value auto k, Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `k` : scalar unsigned value,  parameter of the sum can only take the values 1 and 2.
//!     * `z` : cayley_dickson or real value to process. ( a real input z is treated
//!        as if  complex(z) was entered.
//!
//! **Return value**
//!
//!   Returns the Dirichlet sum \f$  \displaystyle \sum_{n = 0}^\infty \frac{(-1)^n}{(kn+1)^z}\f$
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Dirichlet series](https://en.wikipedia.org/wiki/Dirichlet_series)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/deta.cpp}
//======================================================================================================================
  inline constexpr auto deta = eve::functor<deta_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<eve::unsigned_scalar_value K, typename Z, eve::callable_options O>
  constexpr auto deta_(KYOSU_DELAY(), O const&,
               K const & kk, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      // 15 sig. digits for 0<=real(z)<=171
      // coeffs should sum to about g*g/2+23/24
      //
      using v_t = kyosu::as_real_type_t<Z>;
      using real_t = eve::element_type_t<v_t>;
      auto k = real_t(kk);
      auto [rz, iz] = z;
      auto iszero = is_eqz(z);
      auto isreal = eve::is_eqz(iz);
      auto isneg  = eve::is_ltz(rz);
      auto isnegreal = isreal && isneg;
      auto isodd  = isnegreal && eve::is_odd(rz);
      auto iseven = isnegreal && eve::is_even(rz);

      auto r=eve::half(eve::as(rz)); // reflection point
      auto reflect = rz < r;
      z =  if_else(reflect, oneminus(z), z);

      constexpr std::array<real_t, 64> cm = {
        .27105054312137610850e-19
        -.17889335846010823161e-17,
        .58167446553847312884e-16,
        -.12421162189080181548e-14,
        .19593322190397666205e-13,
        -.24347803504257137241e-12,
        .24823251635643084345e-11,
        -.21352608103961806529e-10,
        .15816215942184366772e-9,
        -.10246226511017621219e-8,
        .58768014045093054654e-8,
        -.30137695171547022183e-7,
        .13931171712321674741e-6,
        -.58440580661848562719e-6,
        .22376124247437700378e-5,
        -.78585149263697370338e-5,
        .25423835243950883896e-4,
        -.76053287924037718971e-4,
        .21106516173760261250e-3,
        -.54504190222378945440e-3,
        .13131884053420191908e-2,
        -.29592166263096543401e-2,
        .62512730682449246388e-2,
        -.12405987285776082154e-1,
        .23176737166455607805e-1,
        -.40840766970770029873e-1,
        .68016197438946063823e-1,
        -.10726959700408922397,
        .16054206784249779846,
        -.22851039270529494523,
        .31007238254065152134,
        -.40215850009669926857,
        .50000000000000000000,
        -.59784149990330073143,
        .68992761745934847866,
        -.77148960729470505477,
        .83945793215750220154,
        -.89273040299591077603,
        .93198380256105393618,
        -.95915923302922997013,
        .97682326283354439220,
        -.98759401271422391785,
        .99374872693175507536,
        -.99704078337369034566,
        .99868681159465798081,
        -.99945495809777621055,
        .99978893483826239739,
        -.99992394671207596228,
        .99997457616475604912,
        -.99999214148507363026,
        .99999776238757525623,
        -.99999941559419338151,
        .99999986068828287678,
        -.99999996986230482845,
        .99999999412319859549,
        -.99999999897537734890,
        .99999999984183784058,
        -.99999999997864739190,
        .99999999999751767484,
        -.99999999999975652196,
        .99999999999998040668,
        -.99999999999999875788,
        .99999999999999994183,
        -.99999999999999999821,
        .99999999999999999997
      };

      Z f{};
      auto j = inc(63*k);
      for(size_t i=0; i < cm.size(); ++i, j -= k)
      {
        f += cm[i]*pow(j, -z);
      }
      if (eve::none(reflect)) return f;
      auto reflection = [&](auto f){
        if (k == 1)
        {
          auto u = dec(exp2(z));
          auto t = -2*u/dec(u)/pow(eve::pi(eve::as(real(z))), z);;
          auto g = t*cospi(eve::half(eve::as(real(z)))*z)*tgamma(z)*f;
          g = if_else(iszero, complex(eve::half(eve::as(real(f)))), g);
          return if_else(iseven, complex(eve::zero(eve::as(real(f)))), g);
        }
        else if (k == 2){
          auto g= pow(eve::two_o_pi(eve::as(real(f))), z)*sinpi(z)*tgamma(z)*f;
          return if_else(isodd, eve::zero(eve::as(real(f))), g);
        }
        else
        {
          return complex(eve::allbits(eve::as(real(f))));
        }
      };
      return if_else(reflect, reflection(f), f);
    }
    else
    {
      return cayley_extend_rev(deta, kk, z);
    }
  }
}
