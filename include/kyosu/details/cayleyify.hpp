//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

auto cayley_extend(auto f, auto z, auto... rs)
{
  auto p = kyosu::pure(z);
  auto az = kyosu::abs(p);
  auto c = f(kyosu::complex(kyosu::real(z), az), rs...);
  return kyosu::real(c) + kyosu::ipart(c)*kyosu::sign(p);
}

auto cayley_extend2(auto f, auto z, auto... rs)
{
  auto p = kyosu::pure(z);
  auto az = kyosu::abs(p);
  auto [c1, c2] = f(kyosu::complex(kyosu::real(z), az), rs...);
  auto s = kyosu::sign(p);
  return kumi::tuple{ kyosu::real(c1) + kyosu::ipart(c1)*s
                    , kyosu::real(c2) + kyosu::ipart(c2)*s};
}
