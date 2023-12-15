//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/abi.hpp>
#include <eve/traits/invoke.hpp>

namespace kyosu::tags { EVE_DEFERRED_INVOKE()     }
namespace kyosu::_    { EVE_DEFERRED_NAMESPACE(); }

//==================================================================================================
//  EVE-related macro that use kyosu::_ as the deferred namespace
//==================================================================================================
#define KYOSU_DEFERS_CALLABLE(NAME) EVE_DEFERS_CALLABLE_FROM(kyosu::_,NAME)

//==================================================================================================
//  EVE-related macro that use eve::detail as the deferred namespace
//==================================================================================================
#define KYOSU_IMPLEMENTS_CALLABLE(TYPE,NAME)  EVE_IMPLEMENTS_CALLABLE_FROM(kyosu::_,TYPE,NAME)

namespace kyosu
{
  template<int Mn, int Mx = Mn>
  requires((Mx != -1 && Mn<=Mx) || Mx == -1)
  struct extractor
  {
    static constexpr unsigned int minimum_valid_index   = Mn;
    static constexpr unsigned int maximum_valid_index   = Mx;
  };

  namespace concepts
  {
    template<typename T>
    concept extractor = eve::callable_entity<T> && requires(T t)
    {
      { t.minimum_valid_index };
      { t.maximum_valid_index };
    };
  }
}
