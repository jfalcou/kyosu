//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_utils2.hpp>
#include <kyosu/details/with_alloca.hpp>
#include <kyosu/functions/if_else.hpp>

namespace ttts::detail
{
  template<typename T> struct typename_impl
  {
    static auto value() noexcept
    {
#if defined(_MSC_VER )
      std::string_view data(__FUNCSIG__);
      auto i = data.find('<') + 1,
        j = data.find(">::value");
      auto name = data.substr(i, j - i);
#else
      std::string_view data(__PRETTY_FUNCTION__);
      auto i = data.find('=') + 2,
        j = data.find_last_of(']');
      auto name = data.substr(i, j - i);
#endif
      return std::string(name.data(), name.size());
    }
  };
}

namespace ttts
{
  /// Provide a string containing the name of the type `T` in readable form.
  template<typename T> inline auto const typename_ = detail::typename_impl<T>::value();

  /// Provide a string containing the name of the type of its parameter in readable form.
  template<typename T> constexpr auto name(T const&){ return typename_<T>; }
}

namespace kyosu::_
{

  template <typename F, typename L, typename L1, typename R, typename ...Ts>
  auto lnext_interval(F const & f, L notdone, L1 test, R& r, Ts ... ts) noexcept
  {
    auto todo = eve::logical_and(notdone, test);
    if constexpr(eve::scalar_value<R>)
    {
      if(todo) { r =  f(ts...); return false_(as(todo)); }
    }
    else
    {
      if(eve::any(todo))
      {
        r = kumi::map([&todo](auto a, auto b) { return if_else(todo,a,b); }, f(ts...), r);
        return eve::logical_notand(todo, notdone);
      };
    }
    return  eve::logical_notand(todo, notdone);
  }

  template <typename F, typename L, typename R, typename ...Ts>
  auto llast_interval(F const & f, L todo, R& r, Ts ... ts) noexcept
  {
    if constexpr(eve::scalar_value<R>)
    {
      if(todo){ r = f(ts...); return false_(as(r));}
      return false_(as(r));
    }
    else
    {
      if(eve::any(todo)) r = kumi::map([&todo](auto a, auto b) { return if_else(todo,a,b); }, f(ts...), r);
      return false_(as(r));
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_jyr01
  //  this internal routine computes jv0 jv1 yv0 and yv1 with v0 in ]0, 1[ and v1 = v0+1
  //===-------------------------------------------------------------------------------------------
  // here nu is always > 0 and z is at most complex
  template<eve::floating_scalar_value N, typename Z>
  auto cb_jyr01( N  v, Z z) noexcept
  {
    using u_t =  eve::underlying_type_t<Z>;
    auto v0 = u_t(v);
//    EVE_ASSERT(eve::is_gtz(v0) && (v0 < N(1)), "v0 is not in ]0, 1[");
    auto v1 = inc(v0); // 1 < v1 < 2

    using u_t = eve::underlying_type_t<Z>;
    const auto eps   = 16*eve::eps(as<u_t>());
    const auto hlf   = eve::half(as<u_t>());
    const auto two   = u_t(2);
    const auto three = u_t(3);
    const auto four  = u_t(4);
    const auto quarter = u_t(0.25);
    const auto twoopi = eve::two_o_pi(as<u_t>());
    const auto invpi = eve::inv_pi(as<u_t>());

    auto az = kyosu::abs(z);
    auto isltzrz = eve::is_ltz(real(z));
    auto isltziz = eve::is_ltz(imag(z));
    z =       if_else(isltzrz, -z, z);
    z =       if_else(isltziz&&isltzrz, conj(z), z);
    auto z2 = sqr(z);

    const Z cone  = kyosu::one(as<Z>());
    const Z cnan  = kyosu::nan(as<Z>());

    Z cjv0(cnan), cjv1(cnan), cyv0(cnan), cyv1(cnan);

    auto br_lt12 =  [&](){
      auto cjv01 = [quarter, hlf, cone, eps, z, z2](auto vl){
        auto cjvl = cone;
        auto cr = cone;
        for (int k=1;k<=40;++k)
        {
          cr *= -quarter*z2/(k*(k+vl));
          cjvl += cr;
          if (eve::all(kyosu::abs(cr) < kyosu::abs(cjvl)*eps)) break;
        }
        auto vg = inc(vl);
        auto ga = eve::tgamma(vg);
        auto ca = pow(hlf*z,vl)/ga;
        return ca*cjvl;
      };
      cjv0 = cjv01(v0);
      cjv1 = cjv01(v1);

      auto cju01 = [&](auto vl){
        auto cjvl = cone;
        auto cr = cone;
        for (int k=1;k<=40;++k) {
          cr *= -quarter*z2/(k*(k-vl));
          cjvl += cr;
          if (eve::all(kyosu::abs(cr) < kyosu::abs(cjvl)*eps)) break;
        }
        auto vg = eve::oneminus(vl);
        auto gb = eve::tgamma(vg);
        auto cb = pow(two/z,vl)/gb;
        return cjvl*cb;
      };
      auto cju0 = cju01(v0);
      auto cju1 = cju01(v1);

      auto [s0, c0] = sinpicospi(v0);
      auto [s1, c1] = sinpicospi(v1);
      cyv0 = fms(cjv0, c0, cju0)/s0;
      cyv1 = fms(cjv1, c1, cju1)/s1;
      return kumi::tuple{cjv0, cyv0, cjv1, cyv1};
    };

    auto br_gt12 =  [&](){
      auto bds = eve::if_else(az >= 50.0, 8, eve::if_else(az >= 35.0, 10, 11));
      auto cjyv01 = [&](auto v0p){
        auto vv = sqr(two*v0p);
        auto cpz = cone;
        auto crp = cone;
        size_t k = 1;
        auto  bound_not_reached = u_t(k) <= bds;
        while (eve::any(bound_not_reached))
        {
          crp = u_t(-0.78125e-2)*crp*(vv-sqr(four*k-three))*
            (vv-sqr(dec(four*k)))/(k*dec(two*k)*z2);
          cpz = if_else(bound_not_reached, cpz+ crp, cpz);
          bound_not_reached = u_t(++k) <= bds;
        }
        auto cqz = cone;
        auto crq = cone;
        k = 1;
        bound_not_reached = u_t(k) <= bds;
        while (eve::any(bound_not_reached))
        {
          crq = u_t(-0.78125e-2)*crq*(vv-sqr(dec(four*k)))*
            (vv-sqr(inc(four*k)))/(k*inc(two*k)*z2);
          cqz += crq;
          cqz = if_else(bound_not_reached, cqz+crp, cqz);
          bound_not_reached = u_t(++k) <= bds;
        }
        cqz *= u_t(0.125)*dec(vv)/z;
        auto zopi = z*invpi;
        auto zk = zopi-(hlf*(v0p+hlf));
        auto ca0 = sqrt(twoopi/z);
        auto [ csk, cck] = sinpicospi(zk);
        return  kumi::tuple{ca0*(cpz*cck-cqz*csk)
            , ca0*(cpz*csk+cqz*cck)};
      };
      kumi::tie(cjv0, cyv0) = cjyv01(v0);
      kumi::tie(cjv1, cyv1) = cjyv01(v1);
      return kumi::tuple{cjv0, cyv0, cjv1, cyv1};
    };

    auto r = kumi::tuple{cjv0, cyv0, cyv1, cjv1};
    auto notdone = kyosu::true_(as<Z>());
    if( eve::any(notdone) )
    {
      notdone = lnext_interval(br_lt12, notdone, az <= u_t(12), r);
      if( eve::any(notdone) )
      {
        llast_interval(br_gt12, notdone, r);
      }
    }
    kumi::tie(cjv0, cyv0, cjv1, cyv1) = r;

    if( eve::any(isltzrz) ) //treating real(z) < 0
    {
      auto eipiv0 = exp_ipi(v0);
      auto eipimv0 = rec(eipiv0);
      auto eipiv1 = -eipiv0;
      auto eipimv1 = -eipimv0;
      cyv0 = if_else(isltzrz, cyv0*eipimv0+2*muli(real(eipimv0))*cjv0, cyv0);
      cyv1 = if_else(isltzrz, cyv1*eipimv1+2*muli(real(eipimv1))*cjv1, cyv1);
      cjv0 = if_else(isltzrz, cjv0*eipiv0, cjv0);
      cjv1 = if_else(isltzrz, cjv1*eipiv1, cjv1);
      if( eve::any(isltziz) ) //treating imag(z) < 0
      {
        cyv0 = if_else(isltziz, conj(cyv0), cyv0);
        cyv1 = if_else(isltziz, conj(cyv1), cyv1);
        cjv0 = if_else(isltziz, conj(cjv0), cjv0);
        cjv1 = if_else(isltziz, conj(cjv1), cjv1);
      }
    }
    return kumi::tuple{cjv0, cyv0, cjv1, cyv1};
  }
}
