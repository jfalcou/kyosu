//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <concepts>

namespace kyosu::_
{

  template<typename T, std::invocable<T*> F>
  decltype(auto) with_alloca(auto size, F f)
  {
    T* p = (T*)(__builtin_alloca_with_align(size*sizeof(T), 8*alignof(T)));
    return f(p);
  }
  
  template<typename T, typename F>
  requires(std::invocable<F, T*, T*>)
    decltype(auto) with_alloca(auto size, F f)
  {
    T* p1 = (T*)(__builtin_alloca_with_align(size*sizeof(T), 8*alignof(T)));
    T* p2 = (T*)(__builtin_alloca_with_align(size*sizeof(T), 8*alignof(T)));
    return f(p1, p2);
  }
}
