//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright: KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>
#include <kyosu/functions/abs.hpp>
#include <kyosu/functions/arg.hpp>
#include <kyosu/details/axis.hpp>

namespace kyosu
{
  template<typename Options>
  struct to_euler_t : eve::callable<to_euler_t, Options, extrinsic_option, intrinsic_option, rad_option, radpi_option>
  {
    template<typename Q, int II, int JJ, int KK>
    requires((concepts::cayley_dickson<Q> && dimension_v<Q> <= 4) || concepts::real<Q>)
    KYOSU_FORCEINLINE constexpr kumi::tuple<as_real_type_t<Q>, as_real_type_t<Q>, as_real_type_t<Q>> operator()(
      Q q0, _::axis<II>, _::axis<JJ>, _::axis<KK>) const noexcept
    {
      auto o = this->options();
      using e_t = std::remove_reference_t<decltype(real(Q()))>;
      using ue_t = eve::element_type_t<e_t>;
      auto q = quaternion(q0);
      std::array<e_t, 4> aq{real(q), ipart(q), jpart(q), kpart(q)};
      constexpr bool is_proper = II == KK; //Proper Euler angles else Tait-Bryan

      auto prepare = [&]() {
        if constexpr (Options::contains(extrinsic))
        {
          constexpr int K = 6 - II - JJ;
          constexpr int I = II;
          constexpr int J = JJ;
          int sign = (I - J) * (J - K) * (K - I) / 2; // even (+1) permutation or odd (-1);

          auto a = aq[0];
          auto b = aq[I];
          auto c = aq[J];
          auto d = aq[K] * sign;
          if constexpr (!is_proper)
          {
            a -= aq[J];
            b += aq[K] * sign;
            c += aq[0];
            d -= aq[I];
          }
          return kumi::tuple{a, b, c, d, sign};
        }
        else
        {
          constexpr int I = KK;
          constexpr int J = JJ;
          constexpr int K = 6 - I - J;
          int sign = (I - J) * (J - K) * (K - I) / 2; // even (+1) permutation or odd (-1);

          auto a = aq[0];
          auto b = aq[I];
          auto c = aq[J];
          auto d = aq[K] * sign;
          if constexpr (!is_proper)
          {
            a -= aq[J];
            b += aq[K] * sign;
            c += aq[0];
            d -= aq[I];
          }
          return kumi::tuple{a, b, c, d, sign};
        }
      };
      auto [a, b, c, d, sign] = prepare();
      auto a2pb2 = eve::sqr(a) + eve::sqr(b);
      auto n2 = a2pb2 + eve::sqr(c) + eve::sqr(d);
      auto theta1 = eve::acos[o](eve::dec(2 * a2pb2 / n2));
      constexpr auto flat = Options::contains(radpi) ? ue_t(1) : eve::pi(eve::as<ue_t>());
      constexpr auto twoflat = Options::contains(radpi) ? ue_t(2) : eve::two_pi(eve::as<ue_t>());
      constexpr auto eps = ue_t(3.0e-8) / flat;

      auto mflat = -flat;
      auto is_safe1 = eve::abs(theta1) >= eps;
      auto is_safe2 = eve::abs(theta1 - flat) >= eps;
      auto is_safe = is_safe1 && is_safe2;

      auto hp = eve::atan2[o](b, a);
      auto hm = eve::atan2[o](-d, c);

      auto theta0 = hp + hm;
      auto theta2 = hp - hm;

      if constexpr (!Options::contains(extrinsic))
      {
        theta0 = eve::if_else(!is_safe, eve::zero, theta0);
        theta2 = eve::if_else(!is_safe1, 2 * hp, theta2);
        theta2 = eve::if_else(!is_safe2, -2 * hm, theta2);
      }
      else
      {
        theta2 = eve::if_else(!is_safe, eve::zero, theta2);
        theta0 = eve::if_else(!is_safe1, 2 * hp, theta0);
        theta0 = eve::if_else(!is_safe2, 2 * hm, theta0);
      }
      theta0 += eve::if_else(theta0 < mflat, twoflat, eve::zero);
      theta0 -= eve::if_else(theta0 > flat, twoflat, eve::zero);
      theta1 += eve::if_else(theta1 < mflat, twoflat, eve::zero);
      theta1 -= eve::if_else(theta1 > flat, twoflat, eve::zero);
      theta2 += eve::if_else(theta2 < mflat, twoflat, eve::zero);
      theta2 -= eve::if_else(theta2 > flat, twoflat, eve::zero);

      // for Tait-Bryan thetas
      if (!is_proper)
      {
        theta2 *= sign;
        theta1 -= flat / 2;
      }
      if constexpr (!Options::contains(extrinsic)) std::swap(theta0, theta2);

      return kumi::tuple{theta0, theta1, theta2};
    }

    KYOSU_CALLABLE_OBJECT(to_euler_t, to_euler_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_euler
  //!
  //! @brief Callable object computing euler angles  from a quaternion.
  //!
  //!  This function build euler angles from a quaternion. Template parameters I, J, K of type int
  //!  are used to choose the euler order.
  //!
  //!  for instance I = 3, J = 2, K = 3 choose the ZYZ sequence.
  //!  the values of I, J, and K must be in {1, 2, 3} and satisfy `I != J && J != K`.
  //!
  //! @groupheader{Header file}
  //!
  //!   @code
  //!   #include kyosu/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template < int I, int J, int K >
  //!      auto to_euler(auto q, axis<I> const & a1, axis<J> const & a2, axis<K> const & a3) noexcept
  //!      requires(I != J && J != K)                                                                              //1
  //!
  //!      template < int I, int J, int K >
  //!      auto to_euler[extrinsic](auto q, axis<I> const & a1, axis<J> const & a2, axis<K> const & a3) noexcept   //1
  //!      requires(I != J && J != K)
  //!
  //!      template < int I, int J, int K >
  //!      auto to_euler[intrinsic](auto q, axis<I> const & a1, axis<J> const & a2, axis<K> const & a3) noexcept   //2
  //!      requires(I != J && J != K)
  //!
  //!      template < int I, int J, int K >
  //!      auto to_euler[radpi][/*all previous options*/](/*all previous overloads*/) noexcept
  //!      requires(I != J && J != K)
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `q` the rotation quaternion (not necesseraly normalized)
  //!  * `a1`, `a2`, `a3`: the axis parameters to be chosen between X_,  Y_, Z_ (two consecutive axes cannot be the same)
  //!  *                    depending of the euler order
  //!
  //!  **Template parameters**
  //!
  //!     * I, J, K: actual parameters can be chosen between axis values X_, Y_, Z_ from
  //!                 which I, J and K are deduced
  //!
  //! **Return value**
  //!
  //!  1. kumi tuple of the three euler angles in radian (or in \f$\pi multiples\f$ if the option `radpi` is used).
  //!     In case of singularity the first angle is 0.
  //!     [extrinsic](https://en.wikipedia.org/wiki/Euler_angles) rotation order is used
  //!  2. Same but in the [intrinsic](https://en.wikipedia.org/wiki/Euler_angles) way
  //!
  //!  @groupheader{External references}
  //!   *  [HAL: Quaternion to Euler angles conversion](https://amu.hal.science/hal-03848730/document)
  //!   *  [Wikipedia: Euler angles](https://en.wikipedia.org/wiki/Euler_angles)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/to_euler.cpp}
  //================================================================================================
  inline constexpr auto to_euler = eve::functor<to_euler_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
