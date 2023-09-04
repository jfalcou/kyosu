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
  template<typename Q0, typename Q1, typename Q2, typename Q3, floating_ordered_value T>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::squad> const&
               , Q0 const& q0, Q1 const& q1, Q2  const & q2, Q3  const & q3
               , T const & t
               ) noexcept
  {
    // t interpolates between q1 and q2
    // q0 and q3 are the preceeding and following quaternion
    // if one want to interpolate between qq0, qq1, ... qqn
    // the first call can take q0 = q1 = qq0 and the last q2 = q3 = qqn
    EVE_ASSERT(eve::all(is_unitary(q0) && is_unitary(q1) && is_unitary(q2) && is_unitary(q3)) , "quaternion parameters must be unitary");
    using e_t = eve::underlying_type_t<Q0>;
    auto mh = (-e_t(0.25));
    auto cq1 = kyosu::conj(q1);
    auto s1 = q1*kyosu::exp((kyosu::log(cq1*q2)+kyosu::log(cq1*q0))*mh);
    auto cq2 = kyosu::conj(q2);
    auto s2 = q2*kyosu::exp((kyosu::log(cq2*q3)*kyosu::log(cq2*q1))*mh);
    return kyosu::slerp(kyosu::slerp(q1, q2, t),
                        kyosu::slerp(s1, s2, t),
                        2*t*eve::oneminus(t));
  }


  template<typename Z1, typename Z2, floating_ordered_value T>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::slerp> const&
               , Z1 const& z1, Z2  z2, T const & t
               ) noexcept
  {
    EVE_ASSERT(eve::all(is_unitary(z1) && is_unitary(z2)), "quaternion parameters must be unitary");
    z2 = kyosu::if_else(eve::is_gez(kyosu::dot(z1, z2)), z2, -z2);
    return z1*kyosu::pow(kyosu::conj(z1)*z2, t);
  }

}
