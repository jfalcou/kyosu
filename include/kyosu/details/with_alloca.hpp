//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <concepts>
#include <span>

namespace kyosu::_
{
  template<typename T, std::invocable<std::span<T>> F>
  decltype(auto) with_alloca(auto size, F f)
  {
    T* p = (T*)(__builtin_alloca_with_align(size*sizeof(T), 8*alignof(T)));
    auto s = std::span(p, size);
    return f(s);
  }

  template<typename T, std::invocable<std::span<T>, std::span<T>> F>
  decltype(auto) with_alloca(auto size, F f)
  {
    T* p1 = (T*)(__builtin_alloca_with_align(size*sizeof(T), 8*alignof(T)));
    T* p2 = (T*)(__builtin_alloca_with_align(size*sizeof(T), 8*alignof(T)));
    auto s1 = std::span(p1, size);
    auto s2 = std::span(p2, size);
    return f(s1, s2);
  }
}
