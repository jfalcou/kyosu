//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include "eve/module/core/regular/if_else.hpp"
#include "kyosu/types/cayley_dickson.hpp"
#include "kyosu/types/concepts.hpp"
#include "kyosu/types/traits.hpp"
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct if_else_t : eve::callable<if_else_t, Options>
  {
    template<typename M, typename T, typename F>
    requires( concepts::cayley_dickson<T> || concepts::cayley_dickson<F>)
    KYOSU_FORCEINLINE constexpr expected_result_t<eve::if_else,M,T,F>
    operator()(M const& m, T const& t, F const& f) const noexcept
    {
      return KYOSU_CALL(m,t,f);
    }

    template<typename M, concepts::real T, concepts::real F>
    KYOSU_FORCEINLINE constexpr auto
    operator()(M const& m, T const& t, F const& f) const noexcept -> decltype(eve::if_else(m,t,f))
    {
      return eve::if_else(m,t,f);
    }

    KYOSU_CALLABLE_OBJECT(if_else_t, if_else_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var if_else
//!   @brief Select a value between two arguments based on a logical mask
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!     constexpr auto if_else(auto x, auto y, auto z ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: logical mask.
//!     * `y`, `z`: values to be selected.
//!
//!   **Return value**
//!
//!        elementwise `y` or `z` according the truth value of `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/if_else.cpp}
//======================================================================================================================
inline constexpr auto if_else = eve::functor<if_else_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename M, typename Z1, typename Z2, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto if_else_(KYOSU_DELAY(), O const&, M const& m, Z1 const& t, Z2 const& f) noexcept
  {
    if constexpr(concepts::cayley_dickson<Z1> && concepts::cayley_dickson<Z2>)
    {
      using type  = as_cayley_dickson_t<Z1,Z2>;
      using ret_t = eve::as_wide_as_t<type,M>;

      return ret_t{ kumi::map ( [&](auto const& v, auto const& w) { return eve::if_else(m, v, w); }
                              , kyosu::convert(t, eve::as_element<type>{})
                              , kyosu::convert(f, eve::as_element<type>{})
                              )
                  };
    }
    else
    {
      auto parts = [&]()
      {
        auto cst = []<typename I>(auto x, I const&) { if constexpr(I::value == 0) return x; else return eve::zero; };

        if      constexpr(!concepts::cayley_dickson<Z2>)
          return kumi::map_index([&](auto i, auto e) { return eve::if_else(m, e, cst(f, i)); }, t);
        else if constexpr(!concepts::cayley_dickson<Z1>)
          return kumi::map_index([&](auto i, auto e) { return eve::if_else(m, cst(t, i), e); }, f);
      }();

      return eve::as_wide_as_t<std::conditional_t<!concepts::cayley_dickson<Z2>,Z1,Z2>,M>{parts};
    }
  }
}
