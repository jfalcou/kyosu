//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/functions/sign.hpp>

namespace kyosu::_
{
  auto cayley_extend(auto f, auto z, auto... rs)
  {
    auto p = kyosu::pure(z);
    auto az = kyosu::abs(p);
    using c_t = complex_t<decltype(az)>;
    auto c = f(c_t(kyosu::real(z), az), rs...);
    return kyosu::real(c) + kyosu::ipart(c)*kyosu::sign(p);
}

  auto cayley_extend_rev(auto f, auto z1, auto z2)
  {
    auto p = kyosu::pure(z2);
    auto az2 = kyosu::abs(p);
    using c_t = complex_t<decltype(az2)>;
    auto c = f(z1,c_t(kyosu::real(z2), az2));
    return kyosu::real(c) + kyosu::ipart(c)*kyosu::sign(p);
  }


  auto cayley_extend2(auto f, auto z, auto... rs)
  {
    auto p = kyosu::pure(z);
    auto az = kyosu::abs(p);
    using c_t = complex_t<decltype(az)>;
    auto [c1, c2] = f(c_t(kyosu::real(z), az), rs...);
    auto s = kyosu::sign(p);
    return kumi::tuple{ kyosu::real(c1) + kyosu::ipart(c1)*s
        , kyosu::real(c2) + kyosu::ipart(c2)*s};
  }
}
