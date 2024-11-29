//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>
#include <kyosu/bessel.hpp>

namespace kyosu
{

  template<typename Options>
  struct bessel_j_t : eve::strict_elementwise_callable<bessel_j_t, Options, eve::spherical_option, eve::cylindrical_option>
  {
    template<eve::scalar_value N, typename Z>
    requires(concepts::real<Z> || concepts::cayley_dickson<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        if constexpr(eve::integral_scalar_value<N>)
        {
          if constexpr(Options::contains(eve::spherical))
          {
//             auto fac = sqrt(pio_2(as(real(z)))*rec(z));
//             auto v = n+eve::half(eve::as(real(z)));
//             return (*this)[this->options().drop(eve::spherical)](v, z)*fac;
            return _::sb_jn(n, z);
          }
          else
            return _::cb_jn(n, z);
        }
        else if constexpr( eve::floating_scalar_value<Z>)
        {
          if constexpr(Options::contains(eve::spherical))
          {
             auto fac = sqrt(pio_2(as(real(z)))*rec(z));
             auto v = n+eve::half(eve::as(real(z)));
             auto r = _::cb_jr(v, z);
             return r*fac;
             //return (*this)[this->options().drop(eve::spherical)](n+eve::half(eve::as(real(n))), z)*sqrt(pio_2(as(real(z)))*rec(z));
          }
          else
            return _::cb_jr(n, z);
        }
      }
      else
        return _::cayley_extend_rev(*this, n, z);
    }

     template<eve::scalar_value N, typename Z, std::size_t S>
    requires(concepts::real<Z> || concepts::complex<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z, std::span<Z, S> js) const noexcept
    {
      if constexpr(Options::contains(eve::spherical))
        return (*this)[this->options().drop(eve::spherical)](n+eve::half(eve::as(real(z))), z)*sqrt(pio_2(as(real(z)))*rec(z));
      else if constexpr(eve::integral_scalar_value<N>)
      {
        std::size_t an = eve::abs(n);
        if (S > n)
        {
          auto doit = [n, z, &js](auto ys){
            _::cb_jyn(n, z, js, ys);
          };
          _::with_alloca<Z>(eve::abs(n)+1, doit);
          return js[n];
        }
        else // js is not sufficiently allocated
        {
          (*this)(S-1, z, js);
          return _::cb_jn(n, z);
        }
      }
      else
      {
        std::size_t an = eve::abs(int(n));
        if (S > an)
        {
          return _::cb_jr(n, z, js);
        }
        else
        {
          (*this)(S-1, z, js);
          return _::cb_jr(n, z);
        }
    }
  }

//     template<typename Z0, typename Z1>
//     requires(eve::integral_scalar_value<Z0> && concepts::cayley_dickson<Z1>)
//     KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& n, Z1 const & z) const noexcept
//     {
//       if constexpr(concepts::complex<Z1> )
//         return _::cb_jn(n, z);
//       else
//         return _::cayley_extend_rev(*this, n, z);
//     }

//     template<eve::integral_scalar_value V0, concepts::real V1>
//     KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept
//     { return eve::bessel_jn(v0,v1); }

    KYOSU_CALLABLE_OBJECT(bessel_j_t, bessel_j_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  bessel_j
//!   @brief Computes the spherical or cylindrical Bessel functions of the first kind,
//!   extended to the complex plane and cayley_dickson  algebras.
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
//!      template<eve;scalar_value N, kyosu::concepts::cayley_dickson T> constexpr auto bessel_j(N n, T z)            noexcept; //1
//!      template<eve;scalar_value N, kyosu::concepts::real T>           constexpr T    bessel_j(N n, T z)            noexcept; //1
//!      template<eve;scalar_value N, kyosu::concepts::cayley_dickson T> constexpr auto bessel_j[spherical](N n, T z) noexcept; //2
//!      template<eve;scalar_value N, kyosu::concepts::real T>           constexpr T    bessel_j[spherical](N n, T z) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar  order (integral or floating)
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. returns \f$\J_n\f$(z) (cylindical).
//!     2. returns \f$\j_n\f$(z) (spherical).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/bessel_j.cpp}
//======================================================================================================================
  inline constexpr auto bessel_j = eve::functor<bessel_j_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
