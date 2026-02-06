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
  struct bessel_k_t
    : eve::strict_elementwise_callable<bessel_k_t, Options, eve::spherical_option, eve::cylindrical_option>
  {
    template<eve::scalar_value N, concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_like_t<N, Z> operator()(N const& n, Z const& z) const noexcept
    {
      return KYOSU_CALL(n, z);
    }

    template<eve::scalar_value N, concepts::complex_like Z, std::size_t S>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_like_t<N, Z> operator()(N const& n,
                                                                          Z const& z,
                                                                          std::span<Z, S> ks) const noexcept
    {
      return KYOSU_CALL(n, z, ks);
    }

    KYOSU_CALLABLE_OBJECT(bessel_k_t, bessel_k_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var  bessel_k
  //!   @brief Computes the spherical or cylindrical modified Bessel functions of the second kind,
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
  //!      template<eve;scalar_value N, cayley_dickson_like T>    constexpr auto bessel_k(N n, T z) noexcept; //1
  //!      template<eve;scalar_value N, complex_like T, size_t S> constexpr auto bessel_k(N n, T z, std::span<Z, S> cis)
  //!      noexcept; //2 template<eve;scalar_value N, cayley_dickson_like T>    constexpr auto bessel_k[spherical](N n,
  //!      T z)                      noexcept; //3 template<eve;scalar_value N, complex_like T, size_t S> constexpr auto
  //!      bessel_k[spherical](N n, T z, std::span<Z, S> sis) noexcept; //4
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`: scalar  order (integral or floating)
  //!     * `z`: Value to process.
  //!     * `sis`, `cis`  : std::span of T
  //!
  //!   **Return value**
  //!
  //!     1. returns \f$K_n\f$(z) (cylindrical).
  //!     2. Same as 1,  but cis is filled by the lesser orders.
  //!     3. returns \f$k_n\f$(z) (spherical).
  //!     4. Same as 3,  but sis is filled by the lesser orders.
  //!
  //!  @note
  //!    * Let \f$ i =  \lfloor |n| \rfloor \f$ and \f$ j=|n|-i\f$. If \f$n\f$ is
  //!        positive the lesser order are \f$(\pm j, \pm(j+1), \dots,  \pm(j+i)) \f$
  //!        with \f$+\f$ sign if \f$n\f$ is positive and  \f$-\f$ sign if \f$n\f$ is negative.
  //!    * The span parameters are filled according the minimum of their allocated size and \f$i\f$.
  //!    * `cylindical` option can be used and its result is identical to the regular call (no option).
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Modified Bessel Function of the second
  //!   Kind](https://mathworld.wolfram.com/BesselFunctionoftheSecondKind.html)
  //!   *  [Wolfram MathWorld: Modified Spherical Bessel Function of the second
  //!   Kind](https://mathworld.wolfram.com/SphericalBesselFunctionoftheSecondKind.html)
  //!   *  [Wikipedia: Bessel function](https://en.wikipedia.org/wiki/Bessel_function)
  //!   *  [DLMF: Modified Bessel functions](https://dlmf.nist.gov/10.25)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/bessel_k.cpp}
  //======================================================================================================================
  inline constexpr auto bessel_k = eve::functor<bessel_k_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename N, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto bessel_k_(KYOSU_DELAY(), O const& o, N n, Z z) noexcept
  {
    if constexpr (concepts::complex<Z>)
    {
      if constexpr (eve::integral_scalar_value<N>)
      {
        if constexpr (O::contains(eve::spherical))
        {
          if (eve::is_ltz(n))
          {
            using u_t = eve::underlying_type_t<Z>;
            return _::sb_kr(u_t(n), z);
          }
          else return _::sb_kn(n, z);
        }
        else return _::cb_kn(n, z);
      }
      else if constexpr (eve::floating_scalar_value<N>)
      {
        if constexpr (O::contains(eve::spherical)) return _::sb_kr(n, z);
        else return _::cb_kr(n, z);
      }
    }
    else return _::cayley_extend_rev(kyosu::bessel_k, n, z);
  }

  template<typename N, typename Z, typename KS, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto bessel_k_(KYOSU_DELAY(), O const& o, N n, Z z, KS& ks) noexcept
  {
    constexpr auto Kind = O::contains(kind_2) ? 2 : 1;
    if constexpr (eve::integral_scalar_value<N>)
    {
      if constexpr (O::contains(eve::spherical))
      {
        if (eve::is_ltz(n))
        {
          using u_t = eve::underlying_type_t<Z>;
          return _::sb_kr(u_t(n), z, ks);
        }
        else return _::sb_kn(n, z, ks);
      }
      else return _::cb_kn(n, z, ks);
    }
    else
    {
      if constexpr (O::contains(eve::spherical)) return _::sb_kr(n, z, ks);
      else return _::cb_kr(n, z, ks);
    }
  }
}
