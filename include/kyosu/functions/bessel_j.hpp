//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/details/bessel.hpp>

namespace kyosu
{

  template<typename Options>
  struct bessel_j_t : eve::strict_elementwise_callable<bessel_j_t, Options, eve::spherical_option, eve::cylindrical_option>
  {
    template<eve::scalar_value N, concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_like_t<N, Z> operator()(N const& n, Z const & z) const noexcept
    {
      return KYOSU_CALL(n, z);
    }

    template<eve::scalar_value N, concepts::complex_like Z, std::size_t S>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_like_t<N, Z> operator()(N const& n, Z const & z, std::span<Z, S> js) const noexcept
    {
      return KYOSU_CALL(n, z, js);
    }


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
//!      template<eve;scalar_value N, kyosu::concepts::cayley_dickson_like T>    constexpr auto bessel_j(N n, T z)                                 noexcept; //1
//!      template<eve;scalar_value N, kyosu::concepts::complex_like T, size_t S> constexpr auto bessel_j(N n, T z, std::span<Z, S> cjs)            noexcept; //2
//!      template<eve;scalar_value N, kyosu::concepts::cayley_dickson_like T>    constexpr auto bessel_j[spherical](N n, T z)                      noexcept; //3
//!      template<eve;scalar_value N, kyosu::concepts::complex_like T, size_t S> constexpr auto bessel_j[spherical](N n, T z, std::span<Z, S> sjs) noexcept; //4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar  order (integral or floating)
//!     * `z`: Value to process.
//!     * `sjs`, `cjs`  : std::span of T
//!
//!   **Return value**
//!
//!     1. returns \f$J_n\f$(z) (cylindrical).
//!     2. Same as 1,  but cjs is filled by the lesser orders.
//!     3. returns \f$j_n\f$(z) (spherical).
//!     4. Same as 3,  but sjs is filled by the lesser orders.
//!
//!  @note
//!    * Let \f$ i =  \lfloor |n| \rfloor \f$ and \f$ j=|n|-i\f$. If \f$n\f$ is
//!        positive the lesser order are \f$(\pm j, \pm(j+1), \dots,  \pm(j+i)) \f$
//!        with \f$+\f$ sign if \f$n\f$ is positive and  \f$-\f$ sign if \f$n\f$ is negative.
//!    * The span parameters are filled according the minimum of their allocated size and \f$i\f$.
//!    * `cylindical` option can be used and its result is identical to the regular call (no option).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Bessel Function of the First Kind](https://mathworld.wolfram.com/BesselFunctionoftheFirstKind.html)
//!   *  [Wolfram MathWorld: Spherical Bessel Function of the First Kind](https://mathworld.wolfram.com/SphericalBesselFunctionoftheFirstKind.html)
//!   *  [Wikipedia: Bessel function](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Bessel functions](https://dlmf.nist.gov/10.2)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/bessel_j.cpp}
//======================================================================================================================
  inline constexpr auto bessel_j = eve::functor<bessel_j_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename N, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto bessel_j_(KYOSU_DELAY(), O const& o, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      if constexpr(eve::integral_scalar_value<N>)
      {
        if constexpr(O::contains(eve::spherical))
        {
          if (eve::is_ltz(n))
          {
            using u_t = eve::underlying_type_t<Z>;
            return _::sb_jr(u_t(n), z);
          }
          else
            return _::sb_jn(n, z);
        }
        else
          return _::cb_jn(n, z);
      }
      else if constexpr( eve::floating_scalar_value<N>)
      {
        if constexpr(O::contains(eve::spherical))
          return _::sb_jr(n, z);
        else
          return _::cb_jr(n, z);
      }
    }
    else
      return _::cayley_extend_rev(kyosu::bessel_j, n, z);
  }

  template<typename N, typename Z, typename JS, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto bessel_j_(KYOSU_DELAY(), O const& o, N n, Z z, JS & js) noexcept
  {
    if constexpr(eve::integral_scalar_value<N>)
    {
      if constexpr(O::contains(eve::spherical))
      {
        if (eve::is_ltz(n))
        {
          using u_t = eve::underlying_type_t<Z>;
          return _::sb_jr(u_t(n), z, js);
        }
        else
          return _::sb_jn(n, z, js);
      }
      else
        return _::cb_jn(n, z, js);
    }
    else
    {
      if constexpr(O::contains(eve::spherical))
        return _::sb_jr(n, z, js);
      else
        return _::cb_jr(n, z, js);
    }
  }
}
