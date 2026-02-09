//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/constants/wrapped.hpp>
#include <kyosu/constants/fnan.hpp>
#include <kyosu/functions/is_fnan.hpp>
#include <kyosu/details/hyperg/hyp2_1.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  2F1
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  template<typename Z> //here Z is always a complex type
  Z hyperg2_1_internal(Z z, Z a, Z b, Z c, auto notdone, auto r) noexcept
  {
    auto re_a = real(a);
    auto re_b = real(b);
    auto re_c = real(c);
    auto ab_condition = (re_b >= re_a);
    auto cab_condition = (re_c >= re_a + re_b);

    using r_t = Z;
    using u_t = eve::underlying_type_t<r_t>;
    auto cinf = kyosu::cinf(as<r_t>());
    u_t five = 5;
    u_t thresh = u_t(1.0e-5);
    u_t spv = 10 * eve::smallestposval(eve::as<u_t>());
    auto na = eve::nearest(re_a);
    auto nb = eve::nearest(re_b);
    auto nc = eve::nearest(re_c);

    auto is_a_neg_int = (a == na) && eve::is_lez(na);
    auto is_b_neg_int = (b == nb) && eve::is_lez(nb);
    auto is_c_neg_int = (c == nc) && eve::is_lez(nc);
    r_t zm1 = dec(z);
    auto z_is_one = (z == kyosu::one(as(z)));
    r_t z_over_zm1 = z / zm1;
    auto abs_z = kyosu::abs(z);
    auto abs_z_over_zm1 = kyosu::abs(z_over_zm1);

    auto br_c_neg_int = [&]() {
      auto t1 = is_a_neg_int && (nc < na);
      auto t2 = is_b_neg_int && (nc < nb);

      auto test = z_is_one && abs_z < abs_z_over_zm1;
      auto fac =
        kyosu::if_else(t1, kyosu::if_else(test, one, kyosu::pow(-zm1, -a)),
                       kyosu::if_else(t2, kyosu::if_else(test, one, kyosu::pow(-zm1, -b)), kyosu::nan(kyosu::as(z))));
      auto pa = kyosu::if_else(t1, a, kyosu::if_else(t2, kyosu::if_else(test, a, b), a));
      auto pb =
        kyosu::if_else(t1, kyosu::if_else(test, b, c - b), kyosu::if_else(t2, kyosu::if_else(test, b, c - a), b));
      return if_else(notdone && test, kyosu::if_else(!(t1 || t2), r, hyp_ps_zero(pa, pb, c, z_over_zm1, notdone) * fac),
                     r);
    };

    auto br_a_neg_int = [&]() { //(is_a_neg_int)
      auto test = is_a_neg_int;
      auto pb = kyosu::if_else(test, b, c - b);
      auto fac = kyosu::if_else(test, one, kyosu::pow(-zm1, -a));
      auto zz = kyosu::if_else(test, z, z_over_zm1);
      return if_else(notdone && test, hyp_ps_zero(a, pb, c, zz, notdone && test) * fac, r);
    };

    auto br_b_neg_int = [&]() { //(is_b_neg_int)
      auto test = is_b_neg_int;
      auto pa = kyosu::if_else(test, a, b);
      auto pb = kyosu::if_else(test, b, c - a);
      auto fac = kyosu::if_else(test, one, kyosu::pow(-zm1, -b));
      auto zz = kyosu::if_else(test, z, z_over_zm1);
      return if_else(notdone && test, hyp_ps_zero(pa, pb, c, zz, notdone && test) * fac, r);
    };

    auto br_cab_and_notab = [&](auto test) { //if cab_condition && !ab_condition
      auto tt = notdone && test;
      auto aa = if_else(tt, b, a);
      auto bb = if_else(tt, a, b);
      return if_else(notdone && test, hyperg2_1_internal(z, aa, bb, c, notdone && test, r), r);
    };

    auto br_notcab_and_ab = [&](auto test) { //if !cab_condition && ab_condition
      return if_else(notdone && test,
                     kyosu::pow(-zm1, c - a - b) * hyperg2_1_internal(z, c - b, c - a, c, notdone && test, r), r);
    };

    auto br_notcab_and_notab = [&](auto test) { //if !cab_condition && !ab_condition
      return if_else(notdone && test, pow(-zm1, c - a - b) * hyperg2_1_internal(z, c - a, c - b, c, notdone && test, r),
                     r);
    };

    auto br_small_zm1 = [&](auto test, auto zm1) { // zm1 < thresh
      auto tzm1 = kyosu::if_else(test, zm1, thresh / 2);
      r = if_else(notdone && test, hyp_ps_one(a, b, c, -tzm1), r);
      return r;
    };

    auto br_rest = [&]() {
      auto abs_zm1 = abs(zm1);
      auto abs_z_inv = eve::rec[eve::pedantic](abs_z);
      auto abs_z_over_zm1 = abs_z / abs_zm1;
      auto abs_zm1_inv = eve::rec[eve::pedantic](abs_zm1);
      auto abs_zm1_over_z = eve::rec[eve::pedantic](abs_z_over_zm1);
      auto are_ac_small = (kyosu::linfnorm(a) < five) && (kyosu::linfnorm(c) < five);
      auto is_cmb_small = (kyosu::linfnorm(c - b) < five);
      auto are_abc_small = are_ac_small && (kyosu::linfnorm(b) < five);
      auto are_a_cmb_c_small = are_ac_small && is_cmb_small;

      auto br_R1 = [&](auto test, auto RR) { // (abs_z <= RR)
        auto zt = kyosu::if_else(test, z, zero);
        r = if_else(test && notdone, hyp_ps_zero(a, b, c, z, test && notdone && test), r);
        return r;
      };

      auto br_R2 = [&](auto test, auto RR) { // (is_cmb_small && (abs_z_over_zm1 <= RR))
        auto zt = kyosu::if_else(test, z, zero);
        r = if_else(notdone && test, kyosu::pow(-zm1, -a) * hyp_ps_zero(a, c - b, c, zt / dec(zt), notdone && test), r);
        return r;
      };

      auto br_R3 = [&](auto test, auto RR) { // (abs_z_inv <= R)
        auto zt = kyosu::if_else(test, z, kyosu::nan(as(z)));
        r = if_else(notdone && test, hyp_ps_infinity(a, b, c, zt, notdone && test), r);
        return r;
      };

      auto br_R4 = [&](auto test, auto RR) { // (is_cmb_small && (abs_zm1_over_z <= R))
        auto z_over_zm1t = kyosu::if_else(test, z_over_zm1, u_t(0.5));
        r = if_else(notdone && test, pow(-zm1, -a) * hyp_ps_infinity(a, c - b, c, z_over_zm1t, notdone && test), r);
        return r;
      };

      auto br_R5 = [&](auto test, auto RR) { // (are_abc_small && (abs_zm1 <= R))
        auto zm1t = kyosu::if_else(test, zm1, u_t(0.4));
        r = if_else(notdone && test, hyp_ps_one(a, b, c, -zm1t), r);
        return r;
      };

      auto br_R6 = [&](auto test, auto RR) { // (are_a_cmb_c_small && (abs_zm1_inv <= R))
        auto zm1t = kyosu::if_else(test, zm1, u_t(3.0));
        r = if_else(notdone && test, hyp_ps_one(a, b, c, -kyosu::rec(zm1t)), r);
        return r;
      };

      auto br_last = [&]() {
        r = if_else(notdone, hyp_ps_cp_rest(a, b, c, z, notdone), r);
        return r;
      };

      if (eve::any(notdone))
      {
        constexpr u_t zp9 = u_t(0.9);
        constexpr u_t zp5 = u_t(0.5);
        constexpr u_t zp1 = u_t(0.1);
        if (eve::any(abs_z <= zp9 || (is_cmb_small && (abs_z_over_zm1 <= zp9))))
        {
          for (u_t R = zp5; R <= zp9; R += zp1)
          {
            if (eve::any(notdone))
            {
              auto t1 = (abs_z <= R);
              notdone = next_interval(br_R1, notdone, t1, r, t1, R);
              if (eve::any(notdone))
              {
                auto t2 = (is_cmb_small && (abs_z_over_zm1 <= R));
                notdone = next_interval(br_R2, notdone, t2, r, t2, R);
              }
              if (eve::none(notdone)) return r;
            }
          }
        }
        if (eve::any((abs_z_inv <= zp9) || (is_cmb_small && (abs_zm1_over_z <= zp9)) ||
                     (are_abc_small && (abs_zm1_inv <= zp9)) || (are_a_cmb_c_small && (abs_zm1_inv <= zp9))))
        {
          for (u_t R = zp5; R <= zp9; R += zp1)
          {
            if (eve::any(notdone))
            {
              auto t3 = (abs_z_inv <= R);
              notdone = next_interval(br_R3, notdone, t3, r, t3, R);
              if (eve::any(notdone))
              {
                auto t4 = (is_cmb_small && (abs_zm1_over_z <= R));
                notdone = next_interval(br_R4, notdone, t4, r, t4, R);
                if (eve::any(notdone))
                {
                  auto t5 = (are_abc_small && (abs_zm1_inv <= R));
                  notdone = next_interval(br_R5, notdone, t5, r, t5, R);
                  if (eve::any(notdone))
                  {
                    auto t6 = (are_a_cmb_c_small && (abs_zm1_inv <= R));
                    notdone = next_interval(br_R6, notdone, t6, r, t6, R);
                  }
                }
              }
            }
          }
          if (eve::none(notdone)) { return r; }
        }
        if (eve::any(notdone)) { last_interval(br_last, notdone, r); }
      }
      return r;
    };

    if (eve::any(notdone))
    {
      auto t1 = (is_real(c) && eve::is_lez(real(c)) && is_flint(real(c)));
      notdone = next_interval(br_c_neg_int, notdone, t1, r);
      if (eve::any(notdone))
      {
        auto t2 = (is_real(a) && eve::is_lez(real(a)) && is_flint(real(a)));
        notdone = next_interval(br_a_neg_int, notdone, t2, r);
        if (eve::any(notdone))
        {
          auto t3 = (is_real(b) && eve::is_lez(real(b)) && eve::is_flint(real(b)));
          notdone = next_interval(br_b_neg_int, notdone, t3, r);
          if (eve::any(notdone))
          {
            auto t61 = cab_condition && !ab_condition;
            notdone = next_interval(br_cab_and_notab, notdone, t61, r, t61);
            if (eve::any(notdone))
            {
              auto t62 = !cab_condition && ab_condition;
              notdone = next_interval(br_notcab_and_ab, notdone, t62, r, t62);
              if (eve::any(notdone))
              {
                auto t63 = !cab_condition && !ab_condition;
                notdone = next_interval(br_notcab_and_notab, notdone, t63, r, t63);
                if (eve::any(notdone)) { notdone = next_interval(br_rest, notdone, notdone, r); }
              }
            }
          }
        }
      }
    }
    return r;
  }

  template<typename Z, eve::sized_product_type<2> T1, eve::sized_product_type<1> T2>
  auto hyperg(Z z0, T1 aa, T2 bb) noexcept -> decltype(kumi::get<0>(T1()) + kumi::get<0>(T2()) + z0)
  {
    using r_t = decltype(kumi::get<0>(T1()) + kumi::get<0>(T2()) + z0);
    using u_t = eve::underlying_type_t<r_t>;
    r_t a(kumi::get<0>(aa));
    r_t b(kumi::get<1>(aa));
    r_t c(kumi::get<0>(bb));
    r_t z(z0);
    // next line to ensure the right cut in complex plane
    z = if_else(is_real(z) && eve::is_greater(real(z), eve::one(kyosu::as_real(z))),
                r_t(real(z), eve::mzero(kyosu::as_real(z))), z);
    r_t r = r_t(kyosu::fnan(eve::as<u_t>()));
    auto notdone = kyosu::true_(eve::as<r_t>());
    return hyperg2_1_internal(z, a, b, c, notdone, r);
  }

  template<typename Z, eve::sized_product_type<2> T1, eve::sized_product_type<1> T2>
  auto hyperg(Z z0, T1 aa, T2 bb, decltype(kyosu::regularized)) noexcept
    -> decltype(kumi::get<0>(T1()) + kumi::get<0>(T2()) + z0)
  {
    using r_t = decltype(kumi::get<0>(T1()) + kumi::get<0>(T2()) + z0);
    using u_t = eve::underlying_type_t<r_t>;
    r_t a(kumi::get<0>(aa));
    r_t b(kumi::get<1>(aa));
    r_t c(kumi::get<0>(bb));
    //if c is a negative integer the value is computed by continuity.
    c = if_else(is_negint(c), eve::next(real(c)), c);
    r_t z(z0);
    // next line to ensure the right cut in complex plane
    z = if_else(is_real(z) && eve::is_greater(real(z), eve::one(kyosu::as_real(z))),
                r_t(real(z), eve::mzero(kyosu::as_real(z))), z);
    r_t r = r_t(kyosu::fnan(eve::as<u_t>()));
    auto notdone = kyosu::true_(eve::as<r_t>());
    return hyperg2_1_internal(z, a, b, c, notdone, r) * tgamma_inv(c);
  }
}
