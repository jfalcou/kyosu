//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace kyosu::_
{

  template<typename T, std::invocable<T*> F>
  decltype(auto) with_alloca(auto size, F f)
  {
    T* p = (T*)(__builtin_alloca_with_align(size*sizeof(T), 8*alignof(T)));
    return f(p);
  }

}
