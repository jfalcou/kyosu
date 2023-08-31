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
  auto dispatch(eve::tag_of<kyosu::is_not_real> const&, C const& c) noexcept
  {
    return kumi::any_of(purepart(c), [](auto const& e) { return eve::is_nez(e); });
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::is_real> const&, C const& c) noexcept
  {
    return kumi::all_of(purepart(c), [](auto const& e) { return eve::is_eqz(e); });
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::is_denormal> const&, C const& c) noexcept
  {
    return kumi::any_of(c, [](auto const& e) { return eve::is_denormal(e); });
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::is_not_denormal> const&, C const& c) noexcept
  {
    return kumi::all_of(c, [](auto const& e) { return eve::is_not_denormal(e); });
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::is_nan> const&, C const& c) noexcept
  {
    return kumi::any_of(c, [](auto const& e) { return eve::is_nan(e); });
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::is_not_nan> const&, C const& c) noexcept
  {
    return kumi::all_of(c, [](auto const& e) { return eve::is_not_nan(e); });
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::is_infinite> const&, C const& c) noexcept
  {
    return kumi::any_of(c, [](auto const& e) { return eve::is_infinite(e); });
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::is_not_infinite> const&, C const& c) noexcept
  {
    return kumi::all_of(c, [](auto const& e) { return eve::is_not_infinite(e); });
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::is_finite> const&, C const& c) noexcept
  {
    return kumi::any_of(c, [](auto const& e) { return eve::is_finite(e); });
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::is_not_finite> const&, C const& c) noexcept
  {
    return kumi::any_of(c, [](auto const& e) { return eve::is_not_finite(e); });
  }

}
