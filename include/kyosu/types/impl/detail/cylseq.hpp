//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace kyosu::_
{

  template<typename F, typename Z, eve::detail::range Ra>
  void dispatch(eve::tag_of<kyosu::cyl_seq>, F f, size_t n, Z z, Ra & cbs) noexcept
  {
    std::cout << "icitte seq" << std::endl;
    if constexpr(concepts::complex<Z>)
    {
      if constexpr(concepts::cayley_dickson<F>)
        *std::begin(cbs) = f;
      else
        *std::begin(cbs) = f(n, z);
      if (n == 0)
        return;
      else
      {
        auto rz = kyosu::rec(z);
        EVE_ASSERT(cbs.size() >= n+1, "cbs has not room enough");
        auto rs =kyosu::_:: R(n, z);
        int i = n-1;

        auto cur = std::rbegin(cbs);
        *cur = f(n, z);
        auto pred = cur++;
        while (i >= 0)
        {
          *cur++ = *pred++*rs;
          rs = 2*(i--)*rz-kyosu::rec(rs);
        }
      }
    }
    else
    {
      auto p = kyosu::pure(z);
      auto az = kyosu::abs(p);
      cyl_bessel_cbs(n, kyosu::complex(kyosu::real(z), az), cbs);
      for(size_t i = 0; i <= n; ++i) cbs[i] = kyosu::real(cbs[i]) + kyosu::ipart(cbs[i])*kyosu::sign(p);
    }
  }

}
