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
      using type = as_cayley_dickson_t<T,U>;
      auto parts = kumi::map([&](auto const& v, auto const& w) { return eve::if_else(m, v, w); }, t, f);

      if constexpr(eve::simd_value<Mask>) return eve::as_wide_as_t<type,Mask>{parts};
      else                                return type{parts};
    }
    else if constexpr(concepts::cayley_dickson<T> && !concepts::cayley_dickson<U>)
    {
      auto parts = kumi::map([&](auto const& v) { return eve::if_else(m, v, f); }, t);

      if constexpr(eve::simd_value<Mask>) return eve::as_wide_as_t<T,Mask>{parts};
      else                                return T{parts};
    }
    else if constexpr(!concepts::cayley_dickson<T> && concepts::cayley_dickson<U>)
    {
      auto parts = kumi::map([&](auto const& w) { return eve::if_else(m, t, w); }, f);

      if constexpr(eve::simd_value<Mask>) return eve::as_wide_as_t<U,Mask>{parts};
      else                                return U{parts};
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

  template<concepts::cayley_dickson  C0, concepts::cayley_dickson  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::dist> const&, C0 const & c0, C1 const &  c1) noexcept
  {
    return kyosu::abs(c0-c1);
  }

  template<concepts::cayley_dickson  C0, concepts::cayley_dickson  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::reldist> const&, C0 const & c0, C1 const & c1) noexcept
  {
    return kyosu::dist(c0, c1)/eve::max(kyosu::abs(c0), kyosu::abs(c1), eve::one(eve::as(abs(c0))));
  }

  template<concepts::cayley_dickson  C0, concepts::cayley_dickson  C1, eve::ordered_value T>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::lerp> const&, C0 const & c0, C1 const & c1, T const & t) noexcept
  {
    using r_t = as_cayley_dickson_t<C0,C1,T>;
    return r_t{kumi::map([&t](auto const& e, auto const & f) { return eve::lerp(e, f, t); }, c0, c1)};
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
}
