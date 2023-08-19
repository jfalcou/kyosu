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
  template<concepts::cayley_dickson C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<conj> const&, C const& c) noexcept
  {
    return C{kumi::map_index([]<typename I>(I, auto const& m) { if constexpr(I::value>0) return -m; else return m;}, c)};
  }

  template<concepts::cayley_dickson C>
  KYOSU_FORCEINLINE constexpr auto dispatch(eve::tag_of<abs> const&, C const& c) noexcept
  {
    return kumi::apply(eve::hypot, c);
  }

  template<concepts::cayley_dickson C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<sqr_abs> const&, C const& c) noexcept
  {
    auto squares = kumi::map([](auto const& e) { return e*e; }, c);
    return kumi::sum( kumi::extract(squares,kumi::index<1>), get<0>(squares));
  }
}
