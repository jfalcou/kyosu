//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace kyosu
{
  /// Computes the number of components for a given Caylay-Dickinson value
  template<typename T>
  inline constexpr unsigned int dimension_v = 1;

  template<concepts::cayley_dickinson T>
  inline constexpr auto dimension_v<T> = eve::element_type_t<std::remove_cvref_t<T>>::static_size;

  /// Computes the a given Caylay-Dickinson-like type from a series of compatible types
  template<unsigned int Dim, typename... Ts>
  requires( requires(Ts... ts) { eve::add(eve::underlying_type_t<Ts>{}...); } )
  struct  as_cayley_dickinson_n
#if !defined(KYOSU_DOXYGEN_INVOKED)
        : as_cayley_dickinson_n<Dim, decltype(eve::add( std::declval<eve::underlying_type_t<Ts>>()...))>
#endif
  {};

#if !defined(KYOSU_DOXYGEN_INVOKED)
  template<unsigned int Dim, typename T>
  struct as_cayley_dickinson_n<Dim, T>
  {
    static constexpr auto card = eve::cardinal_v<T>;
    using cd_t  = cayley_dickinson<eve::underlying_type_t<T>,Dim>;
    using type  = std::conditional_t<card != 1ULL, eve::wide<cd_t,eve::fixed<card>>, cd_t>;
  };

  template<unsigned int Dim, typename... Ts>
  using as_cayley_dickinson_n_t = typename as_cayley_dickinson_n<Dim,Ts...>::type;
#endif

  /// Computes the best Caylay-Dickinson-like type from a series of compatible types
  template<typename... Ts>
  requires( requires(Ts... ts) { eve::add(eve::underlying_type_t<Ts>{}...); } )
  struct as_cayley_dickinson : as_cayley_dickinson_n<std::max( {dimension_v<Ts>...} ), Ts...>
  {};

  template<typename... Ts>
  using as_cayley_dickinson_t = typename as_cayley_dickinson<Ts...>::type;
}
