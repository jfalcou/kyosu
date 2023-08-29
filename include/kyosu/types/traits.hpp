//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <bit>

namespace kyosu
{
  template<eve::floating_scalar_value Type, unsigned int N>
  requires(N> 1 && std::has_single_bit(N))
  struct cayley_dickson;
}

namespace kyosu::_
{
  // Force a type to be looked at as a wide so we can apply wide-like type preserving semantic in type computations
  template<typename T> struct  sema                             { using type = T; };
  template<typename T> struct  sema<eve::logical<T>>  : sema<T> {};
  template<typename T, typename N>
  struct  sema<eve::wide<T,N>>                                  { using type = eve::wide<eve::underlying_type_t<T>>; };
  template<concepts::cayley_dickson T>
  struct  sema<T>                                               { using type = eve::wide<eve::underlying_type_t<T>>; };

  template<typename T>                  using   sema_t  = typename sema<T>::type;

  // Convert a Base type to a potential wide if any appear in T...
  template<typename Base, typename... T>
  using widen = std::conditional_t< std::max({eve::cardinal_v<T>...}) != 1ULL
                                  , eve::as_wide_t<Base,eve::fixed<std::max({eve::cardinal_v<T>...})>>
                                  , eve::element_type_t<Base>
                                  >;
}

namespace kyosu
{
  //====================================================================================================================
  //! @addtogroup traits
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //! @brief Obtains the number of dimensions of the algebra containing a given type
  //!
  //! If `T` satisfies kyosu::concepts::cayley_dickson, evaluates to the number of dimension of the smallest
  //! Cayley-Dickson algebra in which any instance of `T` can be represented.
  //!
  //! If `T` models a value of \f$\mathbb{R}\f$, evaluates to 1.
  //!
  //! @tparam T Type to analyze.
  //====================================================================================================================
  template<typename T>
#if !defined(KYOSU_DOXYGEN_INVOKED)
  inline constexpr unsigned int dimension_v = 1;
#else
  inline constexpr unsigned int dimension_v = *implementation-defined*;
#endif

  template<concepts::cayley_dickson T>
  inline constexpr auto dimension_v<T> = eve::element_type_t<std::remove_cvref_t<T>>::static_size;

  template<typename T>                  struct as_real                          { using type = T; };
  template<typename T,unsigned int Dim> struct as_real<cayley_dickson<T,Dim>>   { using type = T; };
  template<typename T,typename N>       struct as_real<eve::wide<T,N>>
  {
    using type = eve::wide<typename as_real<T>::type,N>;
  };

  //====================================================================================================================
  //! @brief Compute the real type associated to a Cayley-Dickson-like type
  //!
  //! @tparam T Type to convert to a real type.
  //====================================================================================================================
  template<typename T>
  using as_real_t = typename as_real<T>::type;

  template<unsigned int Dim, typename... Ts>
  struct  as_cayley_dickson_n;

  template<unsigned int Dim, typename... Ts>
  requires( Dim > 1 && requires(Ts... ts) { eve::add( std::declval<_::sema_t<Ts>>()...); } )
  struct  as_cayley_dickson_n<Dim,Ts...>
#if !defined(KYOSU_DOXYGEN_INVOKED)
        : as_cayley_dickson_n<Dim, _::widen<decltype(eve::add( std::declval<_::sema_t<Ts>>()...)),Ts...>>
#endif
  {};

#if !defined(KYOSU_DOXYGEN_INVOKED)

  template<unsigned int Dim, typename... Ts>
  requires( Dim > 1 && !requires(Ts... ts) { eve::add( std::declval<_::sema_t<Ts>>()...); } )
  struct  as_cayley_dickson_n<Dim, Ts...> {};

  template<unsigned int Dim, typename T>
  requires(Dim > 1)
  struct as_cayley_dickson_n<Dim, T>
  {
    static constexpr auto card = eve::cardinal_v<T>;
    using cd_t  = cayley_dickson<eve::as_floating_point_t<eve::underlying_type_t<T>>,Dim>;
    using type  = std::conditional_t<card != 1ULL, eve::wide<cd_t,eve::fixed<card>>, cd_t>;
  };
#endif

  //====================================================================================================================
  //! @brief Computes a Cayley-Dickson type of a given dimension
  //!
  //! @tparam Dim Dimension of the Cayley-Dickson algebra to use.
  //! @tparam Ts  Types used to computes the Cayley-Dickson underlying type.
  //====================================================================================================================
  template<unsigned int Dim, typename... Ts>
  using as_cayley_dickson_n_t = typename as_cayley_dickson_n<Dim,Ts...>::type;

  template<typename... Ts>
  requires( requires(Ts... ts) { typename as_cayley_dickson_n<std::max( {dimension_v<Ts>...} ), Ts...>::type; } )
  struct as_cayley_dickson : as_cayley_dickson_n<std::max( {dimension_v<Ts>...} ), Ts...>
  {};

  //====================================================================================================================
  //! @brief Computes the best fitting Cayley-Dickson type from a series of types.
  //!
  //! @tparam Ts  Types used to computes the Cayley-Dickson underlying type.
  //====================================================================================================================
  template<typename... Ts>
  using as_cayley_dickson_t = typename as_cayley_dickson<Ts...>::type;

  //====================================================================================================================
  //!  @}
  //====================================================================================================================
}
