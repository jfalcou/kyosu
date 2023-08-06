//======================================================================================================================
/*
  Kyosu - Complex Math Made Easy
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace kyosu
{
  /// Computes the number of components for a given Caley-Dickinson value
  template<typename T>
  inline constexpr unsigned int dimension_v = 1;

  template<concepts::caley_dickinson T>
  inline constexpr auto dimension_v<T> = eve::element_type_t<std::remove_cvref_t<T>>::static_size;

  /// Computes the best Caley-Dickinson-like type from a series of compatible types
  template<typename... Ts>
  requires( requires(Ts... ts) { eve::add(eve::underlying_type_t<Ts>{}...); } )
  struct as_caley_dickinson
  {
    static constexpr auto dims = std::max( {dimension_v<Ts>...}      );
    static constexpr auto card = std::max( {eve::cardinal_v<Ts>...}  );

    using r_t   = decltype(eve::add( std::declval<eve::underlying_type_t<Ts>>()...));
    using cd_t  = caley_dickinson<r_t,dims>;
    using type  = std::conditional_t<card != 1ULL, eve::wide<cd_t,eve::fixed<card>>, cd_t>;
  };

  template<typename... Ts>
  using as_caley_dickinson_t = typename as_caley_dickinson<Ts...>::type;
}
