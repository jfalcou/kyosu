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
#include <kyosu/types/impl/quaternion/axis.hpp>

namespace kyosu
{
  template<typename Options>
  struct to_euler_t : eve::elementwise_callable<to_euler_t, Options>
  {
    template<typename Q, int II,  int JJ,  int KK, bool Extrinsic>
    requires((concepts::cayley_dickson<Q> && dimension_v<Q> <= 4) || concepts::real<Q>)
      KYOSU_FORCEINLINE constexpr auto operator()(Q  q0
                                                 , _::axis<II>
                                                 , _::axis<JJ>
                                                 , _::axis<KK>
                                                 , _::ext<Extrinsic>) const noexcept
    //   -> kumi::tuple<as_real_t<Q>, as_real_t<Q>, as_real_t<Q>>
    {
      using e_t =  std::remove_reference_t<decltype(real(Q()))>;
      auto q = quaternion(q0);
      std::array<e_t, 4> aq{real(q), ipart(q), jpart(q), kpart(q)};
      constexpr bool is_proper = II == KK; //Proper Euler angles else Tait-Bryan

      auto prepare = [&](){
        if constexpr(Extrinsic)
        {
          constexpr int K = 6-II-JJ;
          constexpr int I = II;
          constexpr int J = JJ;
          int sign = (I-J)*(J-K)*(K-I)/2; // even (+1) permutation or odd (-1);

          auto a = aq[0];
          auto b = aq[I];
          auto c = aq[J];
          auto d = aq[K]*sign;
          if constexpr(!is_proper)
          {
            a -= aq[J];
            b += aq[K]*sign;
            c += aq[0];
            d -= aq[I];
          }
          return kumi::tuple{a, b, c, d, sign};
        }
        else
        {
          constexpr int I = KK;
          constexpr int J = JJ;
          constexpr int K = 6-I-J;
          int sign = (I-J)*(J-K)*(K-I)/2; // even (+1) permutation or odd (-1);

          auto a = aq[0];
          auto b = aq[I];
          auto c = aq[J];
          auto d = aq[K]*sign;
          if constexpr(!is_proper)
          {
            a -= aq[J];
            b += aq[K]*sign;
            c += aq[0];
            d -= aq[I];
          }
          return kumi::tuple{a, b, c, d, sign};
        }
      };
      auto [a, b, c, d, sign] = prepare();
      auto a2pb2 = eve::sqr(a)+eve::sqr(b);
      auto n2 = a2pb2+eve::sqr(c)+eve::sqr(d);
      auto theta1 = eve::acos(eve::dec(2*a2pb2/n2));
      auto eps = 1e-7;
      auto pi  = eve::pi(eve::as<e_t>());
      auto twopi = eve::two_pi(eve::as<e_t>());
      auto mpi = -pi;
      auto is_safe1 = eve::abs(theta1) >= eps;
      auto is_safe2 = eve::abs(theta1 - pi) >= eps;
      auto is_safe = is_safe1 && is_safe2;

      auto hp = eve::atan2(b, a);
      auto hm = eve::atan2(-d, c);

      auto theta0 = hp + hm;
      auto theta2 = hp - hm;

      if constexpr(!Extrinsic)
      {
        theta0 = eve::if_else(!is_safe, eve::zero, theta0);
        theta2 = eve::if_else(!is_safe1, 2*hp, theta2);
        theta2 = eve::if_else(!is_safe2, -2*hm, theta2);
      }
      else
      {
        theta2 = eve::if_else(!is_safe, eve::zero, theta2);
        theta0 = eve::if_else(!is_safe1, 2*hp, theta0);
        theta0 = eve::if_else(!is_safe2, 2*hm, theta0);
      }
      theta0 += eve::if_else(theta0 < mpi, twopi, eve::zero);
      theta0 -= eve::if_else(theta0 >  pi, twopi, eve::zero);
      theta1 += eve::if_else(theta1 < mpi, twopi, eve::zero);
      theta1 -= eve::if_else(theta1 >  pi, twopi, eve::zero);
      theta2 += eve::if_else(theta2 < mpi, twopi, eve::zero);
      theta2 -= eve::if_else(theta2 >  pi, twopi, eve::zero);

      // for Tait-Bryan thetas
      if(!is_proper)
      {
        theta2 *= sign;
        theta1 -= pi / 2;
      }
      if constexpr(!Extrinsic) std::swap(theta0, theta2);

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
  //!   #include eve/module/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template < int I, int J, int K >
  //!      auto to_euler(auto q, axis<I> const & a1, axis<J> const & a2, axis<K> const & a3) noexcept
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
  //!     * I, J, K: actual parameters can be chosen between axis values X_,  Y_, Z_ from
  //!                 which I, J and K are deduced
  //!
  //!
  //!   The computation method is taken from the article: "Quaternion to Euler angles conversion: A
  //!   direct, general and computationally efficient method". PLoS ONE
  //!   17(11): e0276302. https://doi.org/10.1371/journal pone 0276302.
  //!   Evandro Bernardes, and Stephane Viollet
  //!
  //! **Return value**
  //!
  //!    kumi tuple of the three euler angles in radian.
  //!    In case of singularity the first angle is 0.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/to_euler.cpp}
  //================================================================================================
  inline constexpr auto to_euler = eve::functor<to_euler_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
