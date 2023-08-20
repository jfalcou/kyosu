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

  template<concepts::cayley_dickson C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::ceil> const&, C const& c) noexcept
  {
    return C{kumi::map([](auto const& e) { return eve::ceil(e); }, c)};
  }

  template<concepts::cayley_dickson C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::floor> const&, C const& c) noexcept
  {
    return C{kumi::map([](auto const& e) { return eve::floor(e); }, c)};
  }

  template<concepts::cayley_dickson C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::nearest> const&, C const& c) noexcept
  {
    return C{kumi::map([](auto const& e) { return eve::nearest(e); }, c)};
  }

  template<concepts::cayley_dickson C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::trunc> const&, C const& c) noexcept
  {
    return C{kumi::map([](auto const& e) { return eve::trunc(e); }, c)};
  }

  template<concepts::cayley_dickson C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::frac> const&, C const& c) noexcept
  {
    return C{kumi::map([](auto const& e) { return eve::frac(e); }, c)};
  }

  template<concepts::cayley_dickson C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<sqr> const&, C  c) noexcept
  {
    auto squares = kumi::map_index([]<typename I>(I, auto const& m) { if constexpr(I::value>0) return -m*m; else return m*m;}, c);
    auto r = kumi::sum( squares, 0);
    auto a =  2*real(c);
    real(c) = 0;
    return r+a*c;
  }
}