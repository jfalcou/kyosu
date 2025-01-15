//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct average_t : eve::strict_elementwise_callable<average_t, Options>
  {
    template<typename Z0, typename Z1, typename ...Zs>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1> ||( concepts::cayley_dickson<Zs> || ...))
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 z0, Z1 z1, Zs ...zs) const noexcept
    { return KYOSU_CALL(z0,z1,zs...); }

    template<concepts::real V0, concepts::real V1, concepts::real ...Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1, Vs...vs) const noexcept -> decltype(v0+(v1+...+ vs))
    { return eve::average(v0,v1,vs...); }

    KYOSU_CALLABLE_OBJECT(average_t, average_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var average
//!   @brief Computes the average of the parameters.
//!
//!   @groupheader{Header file}
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
//!     constexpr auto average(auto z0, auto... z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1...`: Values to process. Can be a mix of complex and real floating values.
//!
//!   **Return value**
//!
//!     Returns the arithmetic mean of the arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/average.cpp}
//======================================================================================================================
  inline constexpr auto average = eve::functor<average_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename  C0, typename  C1,  typename ...Cs, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto average_(KYOSU_DELAY(), O const&,
                                            C0 const & c0, C1 const &  c1, Cs const &...  cs) noexcept
  {
    using r_t = kyosu::as_cayley_dickson_t<C0,C1,Cs...>;
    if constexpr(sizeof...(cs) == 0)
    {
      using er_t = eve::element_type_t<r_t>;
      return r_t{kumi::map([](auto const& e, auto const& f) { return eve::average(e, f); }
                          , kyosu::convert(c0, eve::as<er_t>())
                          , kyosu::convert(c1, eve::as<er_t>())
                          )
          };
    }
    else
    {
      return (c0+ (c1+ ... + cs)) / (sizeof...(cs) + 2);
    }
  }
}
