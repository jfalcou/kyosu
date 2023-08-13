//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace kyosu
{
  //====================================================================================================================
  //! @name Streaming Operators
  //! @{
  //====================================================================================================================

  /// Stream insertion for Caley-Dickinson based types
  template<concepts::cayley_dickinson CD>
  std::ostream& operator<<(std::ostream& os, CD const& z)
  {
    auto display_positive = [](std::ostream& os,auto e, bool first) -> std::ostream&
    {
      if(first)                     return os << e;
      else if(eve::is_positive(e))  return os << "+ " << e;
      else                          return os << "- " << -e;
    };

    auto basis = [&](auto i)
    {
      constexpr const char* base[4]  = {" ","i ","j ","k "};
      constexpr const char* obase[8] = {"e0 ","e1 ","e2 ","e3 ","e4 ","e5 ","e6 ","e7 "};
      if constexpr(CD::static_size < 8) return base[i]; else return obase[i];
    };

    kumi::for_each_index([&](auto i, auto v) { display_positive(os,v,i == 0) << basis(i);}, z);
    return os;
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
