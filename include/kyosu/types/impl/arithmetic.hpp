//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <iostream>
namespace kyosu::_
{
  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::conj> const&, C const& c) noexcept
  {
    return C{kumi::map_index([]<typename I>(I, auto const& m) { if constexpr(I::value>0) return -m; else return m;}, c)};
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr auto dispatch(eve::tag_of<kyosu::abs> const&, C const& c) noexcept
  {
    return kumi::apply(eve::hypot, c);
  }

 template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::arg> const&, C const& z) noexcept
  {
    if constexpr(kyosu::concepts::complex<C>)
      return eve::pedantic(eve::atan2)(kyosu::imag(z), real(z));
    else
      return eve::pedantic(eve::atan2)(sign(ipart(z))*kyosu::abs(pure(z)), real(z));
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sqr_abs> const&, C const& c) noexcept
  {
    auto squares = kumi::map([](auto const& e) { return e*e; }, c);
    return kumi::sum( kumi::extract(squares,kumi::index<1>), get<0>(squares));
  }

  template<typename Mask, typename T, typename U>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::if_else> const&, Mask const& m, T const& t, U const& f) noexcept
  {
    if constexpr(concepts::cayley_dickson<T> && concepts::cayley_dickson<U>)
    {
      using type  = as_cayley_dickson_t<T,U>;
      using ret_t = eve::as_wide_as_t<type,Mask>;

      return ret_t{ kumi::map ( [&](auto const& v, auto const& w) { return eve::if_else(m, v, w); }
                              , kyosu::convert(t, eve::as_element<type>{})
                              , kyosu::convert(f, eve::as_element<type>{})
                              )
                  };
    }
    else
    {
      auto parts = [&]()
      {
        auto cst = []<typename I>(auto x, I const&) { if constexpr(I::value == 0) return x; else return eve::zero; };
        if      constexpr(!concepts::cayley_dickson<U>)
          return kumi::map_index([&](auto i, auto const& e) { return eve::if_else(m, e, cst(f, i)); }, t);
        else if constexpr(!concepts::cayley_dickson<T>)
          return kumi::map_index([&](auto i, auto const& e) { return eve::if_else(m, cst(t, i), e); }, f);
      }();

      using type = eve::as_wide_as_t<std::conditional_t<!concepts::cayley_dickson<U>,T,U>,Mask>;
      return type{parts};
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::ceil> const&, C const& c) noexcept
  {
    return C{kumi::map([](auto const& e) { return eve::ceil(e); }, c)};
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::floor> const&, C const& c) noexcept
  {
    return C{kumi::map([](auto const& e) { return eve::floor(e); }, c)};
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::nearest> const&, C const& c) noexcept
  {
    return C{kumi::map([](auto const& e) { return eve::nearest(e); }, c)};
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::trunc> const&, C const& c) noexcept
  {
    return C{kumi::map([](auto const& e) { return eve::trunc(e); }, c)};
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::frac> const&, C const& c) noexcept
  {
    return C{kumi::map([](auto const& e) { return eve::frac(e); }, c)};
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sqr> const&, C  c) noexcept
  {
    if constexpr(kyosu::dimension_v<C> <= 2)
    {
      return c*c;
    }
    else
    {
      auto squares = kumi::map_index([]<typename I>(I, auto const& m)
                                     { constexpr auto sgn = (I::value == 0)-(I::value > 0);
                                       return sgn*m*m; }, c);
      auto r = kumi::sum( squares, 0);
      auto a =  2*real(c);
      real(c) = 0;
      return r+a*c;
    }
  }

  template<typename  C0, typename  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::dist> const&, C0 const & c0, C1 const &  c1) noexcept
  {
    return kyosu::abs(c0-c1);
  }

  template<typename  C0, typename  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::reldist> const&, C0 const & c0, C1 const & c1) noexcept
  {
    return kyosu::dist(c0, c1)/eve::max(kyosu::abs(c0), kyosu::abs(c1), eve::one(eve::as(abs(c0))));
  }

  template<typename  C0, typename  C1, eve::ordered_value T>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::lerp> const&, C0 const & c0, C1 const & c1, T const & t) noexcept
  {
    using r_t = as_cayley_dickson_t<C0,C1,T>;
    return r_t{kumi::map([&t](auto const& e, auto const & f) { return eve::lerp(e, f, t); }, r_t(c0), r_t(c1))};
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::inc> const&, C c) noexcept
  {
    real(c) = eve::inc(real(c));
    return c;
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::dec> const&, C c) noexcept
  {
    real(c) = eve::dec(real(c));
    return c;
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::oneminus> const&, C c) noexcept
  {
    return kyosu::inc(kyosu::minus(c));
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::pure> const&, C c) noexcept
  {
    real(c) = 0;
    return c;
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::rec> const&, C c) noexcept
  {
    return conj(c)/sqr_abs(c);
  }

  template<typename C0, concepts::cayley_dickson C1>
  requires(dimension_v<C0> <= dimension_v<C1>)
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<convert> const&, C0 const & c, eve::as<C1> const & tgt) noexcept
  {
    using type = eve::as_wide_as_t<C1, C0>;

    if      constexpr(std::same_as<eve::element_type_t<C0>,C1>) return c;
    else if constexpr(dimension_v<C0> == 1ULL)                  return type{c};
    else
    {
      using u_t = eve::underlying_type_t<C1>;
      return kumi::apply([](auto const&... e) { return type{kyosu::convert(e, eve::as<u_t>{})...}; }, c);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sign> const&, C c) noexcept
  {
    return kyosu::if_else(kyosu::is_nez(c), c/abs(c), C(0));
  }

  template<typename  C0, typename  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::average> const&, C0 const & c0, C1 const &  c1) noexcept
  {
    using r_t = kyosu::as_cayley_dickson_t<C0,C1>;
    using er_t = eve::element_type_t<r_t>;
    return r_t{kumi::map([](auto const& e, auto const& f) { return eve::average(e, f); }
                         , kyosu::convert(c0, eve::as<er_t>())
                         , kyosu::convert(c1, eve::as<er_t>())
                        )
        };
  }

  template<typename...  C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::average> const&, C... cs) noexcept
  {
    using r_t = kyosu::as_cayley_dickson_t<C...>;
    using er_t = eve::element_type_t<r_t>;
    return r_t{kumi::map([](auto const& ... es) { return eve::average(es...); }
                         , kyosu::convert(cs..., eve::as<er_t>())
                        )
        };
  }

  template<typename  C0, typename  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::dot> const&, C0 const & c0, C1 const &  c1) noexcept
  {
    using r_t = kyosu::as_cayley_dickson_t<C0,C1>;
    using er_t = decltype(kyosu::abs(r_t{}));

    if constexpr(eve::floating_value<C1> || eve::floating_value<C0>)
    {
      return kyosu::real(c0)*kyosu::real(c1);
    }
    else
    {
      constexpr auto P = kyosu::dimension_v<C0> < kyosu::dimension_v<C1> ? kyosu::dimension_v<C0> : kyosu::dimension_v<C1>;
      er_t res(0.0f);
      auto sum = [&](auto i, auto x){
        auto [e, f] = x;
        res = eve::fam(res, e, f);
      };
      kumi::for_each_index(sum, kumi::zip( kumi::extract(c0, kumi::index_t<0>{}, kumi::index_t<P>{})
                                         , kumi::extract(c1, kumi::index_t<0>{}, kumi::index_t<P>{})));
      return res;
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::radinpi> const&, C c) noexcept
  {
    using u_t =  eve::element_type_t<C>;
    return c*eve::inv_pi(eve::as<u_t>()); ;
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::proj> const&, C c) noexcept
  {
    using real_t = eve::as<as_real_t<C>>;
    constexpr auto P = kyosu::dimension_v<C>;
    if constexpr (P == 2)
      return if_else(is_infinite(c)
                    , complex(eve::inf(real_t{}), eve::copysign(eve::zero(real_t{}), imag(c)))
                    , c);
    else
    {
      auto isinf = is_infinite(c);
      auto tmp = eve::if_else(isinf, eve::inf(real_t{}), real(c));
      auto setpure = [isinf](auto & x){
        x = eve::if_else(isinf, eve::copysign(eve::zero(real_t{}), x), x);
      };
      kumi::for_each(setpure,  c);
      real(c) = tmp;
      return c;
    }
  }

  template<typename  C0, typename  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::ldiv> const&, C0 const & c0, C1 const &  c1) noexcept
  {
    using r_t = kyosu::as_cayley_dickson_t<C0,C1>;
    if constexpr(dimension_v<r_t> <= 2 || eve::ordered_value<C0>|| eve::ordered_value<C1> )
      return c1/c0;
    else
      return rec(c0)*c1;
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::to_polar> const&, C const& c) noexcept
  {
    if constexpr(kyosu::concepts::complex<C>)
      return kumi::tuple{kyosu::abs(c),  kyosu::arg(c)};
    else
      return kumi::tuple{kyosu::abs(c),  kyosu::arg(c), sign(ipart(c))*sign(pure(c))};
  }

  template<eve::ordered_value T0, eve::ordered_value T1, typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::from_polar> const&
               , T0 const& rho
               , T1 const& theta
               , C const& iz) noexcept
  {
    return rho*kyosu::exp(theta*iz);
  }
}
