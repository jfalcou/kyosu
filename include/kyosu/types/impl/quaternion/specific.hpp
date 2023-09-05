//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace kyosu::_
{

 template<typename Z, int II,  int JJ,  int KK, bool Extrinsic>
 KYOSU_FORCEINLINE constexpr
 auto dispatch(eve::tag_of<kyosu::to_euler> const&
              , Z const& q0
              , axes<II>
              , axes<JJ>
              , axes<KK>
              , ext<Extrinsic>
              ) noexcept
  requires(II != JJ && JJ != KK)
  {
    using e_t =  std::remove_reference_t<decltype(real(Z()))>;
    auto q = to_quaternion(q0);
    std::array<e_t, 4> aq{get<0>(q), get<1>(q), get<2>(q), get<3>(q)};
    EVE_ASSERT(eve::all(is_nez(q)), "some quaternion are null");
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
    auto theta1 = eve::acos(dec(2*a2pb2/n2));
    auto eps = 1e-7;
    auto pi  = eve::pi(as<e_t>());
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


//   template<typename Q0, typename Q1, typename Q2, typename Q3, floating_ordered_value T>
//   KYOSU_FORCEINLINE constexpr
//   auto dispatch(eve::tag_of<kyosu::squad> const&
//                , Q0 const& q0, Q1 const& q1, Q2  const & q2, Q3  const & q3
//                , T const & t
//                ) noexcept
//   {
//     // t interpolates between q1 and q2
//     // q0 and q3 are the preceeding and following quaternion
//     // if one want to interpolate between qq0, qq1, ... qqn
//     // the first call can take q0 = q1 = qq0 and the last q2 = q3 = qqn
//     EVE_ASSERT(eve::all(is_unitary(q0) && is_unitary(q1) && is_unitary(q2) && is_unitary(q3)) , "quaternion parameters must be unitary");
//     using e_t = eve::underlying_type_t<Q0>;
//     auto mh = (-e_t(0.25));
//     auto cq1 = kyosu::conj(q1);
//     auto s1 = q1*kyosu::exp((kyosu::log(cq1*q2)+kyosu::log(cq1*q0))*mh);
//     auto cq2 = kyosu::conj(q2);
//     auto s2 = q2*kyosu::exp((kyosu::log(cq2*q3)*kyosu::log(cq2*q1))*mh);
//     return kyosu::slerp(kyosu::slerp(q1, q2, t),
//                         kyosu::slerp(s1, s2, t),
//                         2*t*eve::oneminus(t));
//   }


//   template<typename Z1, typename Z2, floating_ordered_value T>
//   KYOSU_FORCEINLINE constexpr
//   auto dispatch(eve::tag_of<kyosu::slerp> const&
//                , Z1 const& z1, Z2  z2, T const & t
//                ) noexcept
//   {
//     EVE_ASSERT(eve::all(is_unitary(z1) && is_unitary(z2)), "quaternion parameters must be unitary");
//     z2 = kyosu::if_else(eve::is_gez(kyosu::dot(z1, z2)), z2, -z2);
//     return z1*kyosu::pow(kyosu::conj(z1)*z2, t);
//   }

}
