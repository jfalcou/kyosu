//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <kyosu/functions/to_complex.hpp>
namespace kyosu::_
{

 template<typename Z, int II,  int JJ,  int KK, bool Extrinsic>
 KYOSU_FORCEINLINE constexpr
 auto dispatch(eve::tag_of<kyosu::to_euler> const&
              , Z const& q0
              , axis<II>
              , axis<JJ>
              , axis<KK>
              , ext<Extrinsic>
              ) noexcept
  requires(II != JJ && JJ != KK)
  {
    using e_t =  std::remove_reference_t<decltype(real(Z()))>;
    auto q = quaternion(q0);
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

  template<typename Z, bool normalize>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::to_rotation_matrix> const&
               , Z q
               , _::norming<normalize>) noexcept
    {
      if constexpr (!normalize)
      {
        EVE_ASSERT(eve::all(kyosu::is_unitary(q)), "some quaternions are not unitary");
      }
      else
      {
        q =  sign(q);
      }
      if constexpr(kyosu::concepts::complex<Z>)
      {
        auto q0 = real(q);
        auto q1 = imag(q);
        auto q02 = 2*sqr(q0)-1;
        auto q0q1= 2*q0*q1;
        using m_t = std::array< std::array<Z, 3>, 3>;
        return m_t{{1, 0, 0}, {0, q02, -q0q1}, {0, q0q1, q02}};
      }
      else
      {
        auto q0 = real(q);
        auto q1 = ipart(q);
        auto q2 = jpart(q);
        auto q3 = kpart(q);

        // First row of the rotation matrix
        auto r00 = 2 * (sqr(q0) + sqr(q1)) - 1;
        auto r01 = 2 * (q1 * q2 - q0 * q3);
        auto r02 = 2 * (q1 * q3 + q0 * q2);

        // Second row of the rotation matrix
        auto r10 = 2 * (q1 * q2 + q0 * q3);
        auto r11 = 2 * (sqr(q0) + sqr(q2)) - 1;
        auto r12 = 2 * (q2 * q3 - q0 * q1);

        // Third row of the rotation matrix
        auto r20 = 2 * (q1 * q3 - q0 * q2);
        auto r21 = 2 * (q2 * q3 + q0 * q1);
        auto r22 = 2 * (sqr(q0) + sqr(q3)) - 1;

        // 3x3 rotation matrix
        using e_t = std::decay_t<decltype(q0)>;
        using l_t = std::array<e_t, 3>;
        using m_t = std::array<l_t, 3>;
        std::array<e_t, 3> l1{r00, r01, r02};
        std::array<e_t, 3> l2{r10, r11, r12};
        std::array<e_t, 3> l3{r20, r21, r22};
        return m_t{l1, l2, l3};
      }
    }

  template<typename Z, bool normalize>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::to_rotation_matrix> const&
               , Z const& q) noexcept
  {
    return to_rotation_matrix(q, _::norming<normalize>{});
  }

  template<typename Z>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::to_multipolar> const&
               , Z const& q) noexcept
  {
    auto c0 = complex(get<0>(q), get<1>(q));
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto z =  eve::zero(eve::as(abs(c0)));
      return kumi::tuple{abs(c0), arg(c0), z, z};
    }
    else
    {
      auto c1 = complex(get<2>(q), get<3>(q));
      return kumi::tuple{abs(c0), arg(c0), abs(c1), arg(c1)};
    }
  }

  template<typename Z>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::to_cylindrical> const&
               , Z const& q) noexcept
  {
    auto c0 = complex(get<0>(q), get<1>(q));
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto z =  eve::zero(eve::as(abs(c0)));
      return kumi::tuple{abs(c0), arg(c0), z, z};
    }
    else
    {
      return kumi::tuple{abs(c0), arg(c0), get<2>(q), get<3>(q) };
    }
  }

  template<typename Z>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::to_semipolar> const&
               , Z const& q) noexcept
  {
    auto c0 = complex(get<0>(q), get<1>(q));
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto z =  eve::zero(eve::as(abs(c0)));
      return kumi::tuple{abs(c0), z, arg(c0), z};
    }
    else
    {
      auto rho = kyosu::abs(q);
      auto c0 = complex(get<0>(q), get<1>(q));
      auto c1 = complex(get<2>(q), get<3>(q));
      auto alpha = eve::pedantic(eve::atan2)(abs(c1), abs(c0));
      auto theta1 = arg(c0);
      auto theta2 = arg(c1);
      return kumi::tuple{rho, alpha, theta1, theta2};
    }
  }

  template<typename Z>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::to_spherical> const&
               , Z q) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto c0 = complex(get<0>(q), get<1>(q));
      auto z =  eve::zero(eve::as(abs(c0)));
      return kumi::tuple{abs(c0), arg(c0), z, z};
    }
    else
    {
      auto rho = kyosu::abs(q);
      auto phi2 = eve::asin(get<3>(q)/rho);
      get<3>(q) = 0;
      auto rho1 = kyosu::abs(q);
      auto phi1 = eve::asin(get<2>(q)/rho1);
      get<2>(q) = 0;
      auto rho2 = kyosu::abs(q);
      auto theta= eve::asin(get<1>(q)/rho2);
      return kumi::tuple{rho, theta, phi1, phi2};
    }
  }

  template<typename Z, typename T, bool normalize>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::rotate_vec> const&
               , Z const & q
               , std::span<T, 3> const & v
               , _::norming<normalize>) noexcept
  {
    using e_t = std::decay_t<decltype(kyosu::real(q))>;
    using v_t = decltype(T()+e_t());
    if constexpr (!normalize) EVE_ASSERT(eve::all(eve::pedantic(kyosu::is_unitary)(q)), "some quaternions are not unitary");
    std::array<v_t, 3> w, wp;
    using a_t = decltype(kyosu::abs(q));
    a_t fac(2);
    if constexpr(normalize) fac *= kyosu::rec(kyosu::sqr_abs(q));
    auto [r, i, j, k] = q;
    w[0] = eve::fma(r, v[0], eve::diff_of_prod(j, v[2], k, v[1]));
    w[1] = eve::fma(r, v[1], eve::diff_of_prod(k, v[0], i, v[2]));
    w[2] = eve::fma(r, v[2], eve::diff_of_prod(i, v[1], j, v[0]));

    wp[0] = eve::fam(v[0], fac, eve::diff_of_prod(j, w[2], k, w[1]));
    wp[1] = eve::fam(v[1], fac, eve::diff_of_prod(k, w[0], i, w[2]));
    wp[2] = eve::fam(v[2], fac, eve::diff_of_prod(i, w[1], j, w[0]));
    return wp;
  }

  template<typename Z, typename T>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::rotate_vec> const&
               , Z const & q
               , std::span<T, 3> const & v) noexcept
  {
    return rotate_vec(q, v, _::norming<true>{});
  }

  template<typename Z>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::rot_axis> const&
               , Z const& q) noexcept
  {
    using e_t = std::decay_t<decltype(real(q))>;
    auto invn = eve::rec(kyosu::abs(kyosu::pure(q)));
    invn = eve::if_else(eve::is_nan(invn), eve::zero, invn);
    std::array<e_t, 3> v{kyosu::ipart(q)*invn, kyosu::jpart(q)*invn, kyosu::kpart(q)*invn};
    return v;
  }

  template<typename Z>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::rot_angle> const&
                           , const Z &q) noexcept
  {
    return 2*eve::pedantic(eve::atan2)(kyosu::abs(kyosu::pure(q)), kyosu::real(q));
  }

  template<typename Z>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::to_angle_axis> const&
                           , Z q) noexcept
  {
    q =  sign(q);
    using e_t = std::decay_t<decltype(real(q))>;
    auto ap = kyosu::abs(pure(q));
    auto invn = eve::rec(ap);
    invn = eve::if_else(eve::is_infinite(invn), eve::zero, invn);
    std::array<e_t, 3> v{kyosu::ipart(q)*invn, kyosu::jpart(q)*invn, kyosu::kpart(q)*invn};
    auto a =  2*eve::pedantic(eve::atan2)(ap, kyosu::real(q));
    return kumi::tuple{a, v};
  }

  template<typename Z1, typename Z2, eve::floating_ordered_value T>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::slerp> const&
               , Z1 z1, Z2  z2, T const & t
               ) noexcept
  {
    EVE_ASSERT(eve::all(is_unitary(z1) && is_unitary(z2)), "quaternion parameters must be unitary");
    auto gez = eve::is_gez(kyosu::dot(z1, z2));
    auto mix = kyosu::if_else(gez, z2, -z2);
    return z1*kyosu::pow(kyosu::conj(z1)*mix, t);
  }

}
