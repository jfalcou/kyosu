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
  //! @name Compound Assignment Operators
  //! @{
  //====================================================================================================================

  /// Adds the real value `other` to `self` and returns the new value of `self`.
  constexpr auto& operator+=(concepts::cayley_dickson auto& self, eve::ordered_value auto other) noexcept
  requires( requires {get<0>(self) += other;} )
  {
    get<0>(self) += other;
    return self;
  }

  /// Adds the Caley-dickson value `other` to `self` and returns the new value of `self`.
  template<concepts::cayley_dickson Self, concepts::cayley_dickson Other>
  requires(dimension_v<Other> <= dimension_v<Self>)
  constexpr auto& operator+=(Self& self, Other const& other) noexcept
  {
    kumi::for_each_index( [&]<typename I>(I,auto const& o) { get<I::value>(self) += o; }, other);
    return self;
  }

  /// Substracts the real value `other` from `self` and returns the new value of `self`.
  constexpr auto& operator-=(concepts::cayley_dickson auto& self, eve::ordered_value auto other) noexcept
  requires( requires {get<0>(self) -= other;} )
  {
    get<0>(self) -= other;
    return self;
  }

  /// Substracts the Caley-dickson value `other` from `self` and returns the new value of `self`.
  template<concepts::cayley_dickson Self, concepts::cayley_dickson Other>
  requires(dimension_v<Other> <= dimension_v<Self>)
  constexpr auto& operator-=(Self& self, Other const& other) noexcept
  {
    kumi::for_each_index( [&]<typename I>(I,auto const& o) { get<I::value>(self) -= o; }, other);
    return self;
  }

  /// Multiplies `self` by the  real value `other`  and returns the new value of `self`.
  constexpr auto& operator*=(concepts::cayley_dickson auto& self, eve::ordered_value auto other) noexcept
  requires( requires {get<0>(self) *= other;} )
  {
    kumi::for_each( [&](auto& s) { s *= other; }, self);
    return self;
  }

  /// Multiplies `self` by the Caley-dickson value `other`  and returns the new value of `self`.
  template<concepts::cayley_dickson Self, concepts::cayley_dickson Other>
  requires(dimension_v<Other> <= dimension_v<Self>)
  constexpr Self& operator*=(Self& self, Other const& other) noexcept
  {
    if constexpr(dimension_v<Self> == 2)
    {
      // complex is the floor state and need optimized handling with FMAs
      auto [ra,ia] = self;
      auto [rb,ib] = other;

      self = as_cayley_dickson_t<Self,Other>{eve::fms(ra,rb,ib*ia), eve::fma(ra,ib,ia*rb)};
    }
    else if constexpr(dimension_v<Self> == dimension_v<Other>)
    {
      constexpr auto sz = dimension_v<Self>/2;
      auto ria  = kumi::split(self ,kumi::index<sz>);
      auto rib  = kumi::split(other,kumi::index<sz>);

      using cd_t = as_cayley_dickson_n_t<sz,as_real_type_t<Self>,as_real_type_t<Other>>;
      cd_t  ra{get<0>(ria)}, ia{get<1>(ria)}
          , rb{get<0>(rib)}, ib{get<1>(rib)};

      // Cayley-Dickson construction : (a,b) x  (c,d)= (a x c - conj(d) x b       , d x a + b x conj(c))
      self = as_cayley_dickson_t<Self,Other>{kumi::cat((ra * rb) - (conj(ib) * ia),(ib * ra) + (ia * conj(rb)))};
    }
    else
    {
      // Optimize the mixed dimensions to not generate spurious operation with 0s
      constexpr auto sz = dimension_v<Self>/2;
      constexpr auto idx  = kumi::index<sz>;
      auto ria  = kumi::split(self,idx);

      using cd_t = as_cayley_dickson_n_t<sz,as_real_type_t<Self>,as_real_type_t<Other>>;
      cd_t ra{get<0>(ria)}, ia{get<1>(ria)};
      self = as_cayley_dickson_t<Self,Other>{kumi::cat(ra * other,ia * conj(other))};
    }

    return self;
  }

  /// Divides `self` by the  real value `other` and returns the new value of `self`.
  constexpr auto& operator/=(concepts::cayley_dickson auto& self, eve::ordered_value auto other) noexcept
  requires( requires {get<0>(self) /= other;} )
  {
    kumi::for_each( [&](auto& s) { s /= other; }, self);
    return self;
  }

  /// Divides  `self` by the Caley-dickson value `other`  and returns the new value of `self`.
  template<concepts::cayley_dickson Self, concepts::cayley_dickson Other>
  requires(dimension_v<Other> <= dimension_v<Self>)
  constexpr Self& operator/=(Self& self, Other const& other) noexcept
  {
    auto r1 =  (self * if_else(is_infinite(other), eve::zero, conj(other)/sqr_abs(other)));
    auto eqzother =  is_eqz(other);
    if(eve::none(eqzother))
    {
      self = r1;
    }
    else
    {
      self = if_else(is_eqz(other), self/real(other), r1);
    }
    return self;
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================

  //====================================================================================================================
  //  Requirements traps
  //  If a compilation error occurs and references one of those overloads, this means you tried to call an operator
  //  in an incorrect setup like:
  //    * compound assignment between a scalar and a wide (like Complex += Wide)
  //    * compound assignment between two Caley-dickson of incompatible dimension_v (like Complex += Quaternion)
  //====================================================================================================================
#if !defined(KYOSU_DOXYGEN_INVOKED)
  template<concepts::cayley_dickson Self, concepts::cayley_dickson Other>
  requires(dimension_v<Other> > dimension_v<Self>)
  constexpr auto& operator+=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator+=(concepts::cayley_dickson auto& self, eve::ordered_value auto v) noexcept
  requires( !requires {get<0>(self) += v;} ) = delete;

  template<concepts::cayley_dickson Self, concepts::cayley_dickson Other>
  requires(dimension_v<Other> > dimension_v<Self>)
  constexpr auto& operator-=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator-=(concepts::cayley_dickson auto& self, eve::ordered_value auto v) noexcept
  requires( !requires {get<0>(self) -= v;} ) = delete;

  template<concepts::cayley_dickson Self, concepts::cayley_dickson Other>
  requires(dimension_v<Other> > dimension_v<Self>)
  constexpr auto& operator*=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator*=(concepts::cayley_dickson auto& self, eve::ordered_value auto v) noexcept
  requires( !requires {get<0>(self) *= v;} ) = delete;

  template<concepts::cayley_dickson Self, concepts::cayley_dickson Other>
  requires(dimension_v<Other> > dimension_v<Self>)
  constexpr auto& operator/=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator/=(concepts::cayley_dickson auto& self, eve::ordered_value auto v) noexcept
  requires( !requires {get<0>(self) /= v;} ) = delete;
#endif
}
