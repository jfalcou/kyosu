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
  template<unsigned int I, unsigned int Min>
  struct extractor
  {
    using   is_extractor             = void;
    static constexpr unsigned int index   = I;
    static constexpr unsigned int minimal = Min;
  };

  namespace concepts
  {
    template<typename T>
    concept extractor = requires(T) { typename T::is_extractor; };
  }
}
