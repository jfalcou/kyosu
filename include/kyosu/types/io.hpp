//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <string>

namespace kyosu
{
  //====================================================================================================================
  //! @name Streaming Operators
  //! @related cayley_dickson
  //! @{
  //====================================================================================================================

  /// Stream insertion for Cayley-dickson based types
  template<concepts::cayley_dickson CD>
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
      constexpr const char* base[8] = {" ","i ","j ","k ","l ","li ","lj ", "lk "};
      if constexpr(CD::static_dimension < 16) return base[i]; else return "z"+ std::to_string(i) + " ";
    };

    kumi::for_each_index([&](auto i, auto v) { display_positive(os,v,i == 0) << basis(i);}, z);
    return os;
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
