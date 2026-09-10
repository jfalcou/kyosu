//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <iostream>
#include <kyosu/details/bessel/bessel_utils2.hpp>

namespace kyosu::_
{
  /////////////////////////////////
  // needed by implementations of
  // airy_ai
  // airy_bi
  // airy
  /////////////////////////////////
  // utilities
  // zet
  // ai
  // bi
  // aibi
  /////////////////////////////////
  // implementation is done using j and y functions

  //===-------------------------------------------------------------------------------------------
  // zet
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE auto zet(Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto sqz = sqrt(z);
    auto zzeta = (pow(z, u_t(1.5)) * 2) / 3;
    return kumi::tuple{sqz / kyosu::sqrt_3(as(z)), zzeta};
  }

  //===-------------------------------------------------------------------------------------------
  // ai
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE Z ai(Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto third = eve::third(as<u_t>());
    auto invpi = eve::inv_pi(as<u_t>());
    auto br_im_eq_0 = [](auto z) { return Z(eve::airy_ai(real(z))); };

    auto br_re_lt_0 = [third](auto z) {
      auto mz = -z;
      auto zet = 2 * pow(mz, u_t(1.5)) / 3;
      return third * sqrt(mz) * (cb_jr(-third, zet) + cb_jr(third, zet));
    };

    auto br_re_gt_0 = [third, invpi](auto z) {
      auto zet = 2 * pow(z, u_t(1.5)) / 3;
      std::array<Z, 1> ks;
      auto r = invpi * sqrt(z / 3) * cb_kr(third, zet, ks);
      return r;
    };

    auto notdone = eve::true_(as<Z>());
    Z r = kyosu::nan(as<Z>());
    auto re = real(z);
    if (eve::any(notdone))
    {
      notdone = next_interval(br_im_eq_0, notdone, is_real(z), r, z);
      if (eve::any(notdone))
      {
        notdone = next_interval(br_re_gt_0, notdone, eve::is_gez(re), r, z);
        if (eve::any(notdone))
        {
          notdone = last_interval(br_re_lt_0, notdone, r, z);
        }
      }
    }
    return r;
  }

  //===-------------------------------------------------------------------------------------------
  // bi
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE auto bi(Z z) noexcept
  {
    std::cout << "bi " << z << std::endl;
    using u_t = eve::underlying_type_t<Z>;
    auto third = eve::third(as<u_t>());
    auto br_im_eq_0 = [](auto z) { return Z(eve::airy_bi(real(z))); };

    auto br_re_lt_0 = [third](auto z) {
      auto zet = 2 * pow(-z, u_t(1.5)) / 3;
      return (cb_ir(-third, zet) - cb_ir(third, zet)) * sqrt(-z / 3);
    };

    auto br_re_gt_0 = [third](auto z) {
      auto zet = 2 * pow(z, u_t(1.5)) / 3;
      return sqrt(z / 3) * (cb_ir(third, zet) + cb_ir(-third, zet));
    };

    auto notdone = eve::true_(as<Z>());
    Z r = kyosu::nan(as<Z>());
    auto re = real(z);
    auto imlt0 = eve::is_ltz(imag(z));
    z = if_else(imlt0, conj(z), z);
    if (eve::any(notdone))
    {
      notdone = eve::next_interval(br_im_eq_0, notdone, is_real(z), r, z);
      if (eve::any(notdone))
      {
        notdone = next_interval(br_re_gt_0, notdone, eve::is_gtz(re), r, z);
        if (eve::any(notdone))
        {
          notdone = eve::last_interval(br_re_lt_0, notdone, r, z);
        }
      }
    }
    return if_else(imlt0, conj(r), r);
  }
}
