//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/lj0.hpp>
#include <kyosu/types/impl/detail/bessel_utils.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_lbessel_jn
  //===-------------------------------------------------------------------------------------------

  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_lbessel_jn>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      Z r{}, s{};
      if (n > 0)
      {
        auto rz = rec(z);
        auto rn = R(n, z);
        auto lri = log(rn);
        for(int i=n-1; i > 0; --i)
        {
          rn = 2*i*rz-rec(rn);
          lri += log(rn);
        }
        s = log(kyosu::cyl_bessel_j0(z))-lri;
      }
      else s =  kyosu::log(cyl_bessel_j0(z));
      using e_t =  eve::element_type_t<Z>;
      return if_else(is_nez(z), arg_adjust(s), kyosu::complex(eve::minf(eve::as<e_t>())));
    }
    else
    {
      return cayley_extend_rev(cyl_lbessel_jn, n, z);
    }
  }

}
