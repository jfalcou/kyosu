//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/as.hpp>
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
  inline constexpr auto dimension_v<T> = eve::element_type_t<std::remove_cvref_t<T>>::static_dimension;

  template<typename T>                  struct as_real_type                          { using type = T; };
  template<typename T,unsigned int Dim> struct as_real_type<cayley_dickson<T,Dim>>   { using type = T; };
  template<typename T,typename N>       struct as_real_type<eve::wide<T,N>>
  {
    using type = eve::wide<typename as_real_type<T>::type,N>;
  };

  //====================================================================================================================
  //! @brief Compute the real type associated to a Cayley-Dickson-like type
  //!
  //! @tparam T Type to convert to a real type.
  //====================================================================================================================
  template<typename T>
  using as_real_type_t = typename as_real_type<T>::type;

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
  //! @tparam Ts  Types used to compute the Cayley-Dickson underlying type.
  //====================================================================================================================
  template<unsigned int Dim, typename... Ts>
  using as_cayley_dickson_n_t = typename as_cayley_dickson_n<Dim,Ts...>::type;

  template<typename... Ts>
  requires( requires(Ts... ts) { typename as_cayley_dickson_n<std::max( {dimension_v<Ts>...} ), Ts...>::type; } )
  struct as_cayley_dickson : as_cayley_dickson_n<std::max( {dimension_v<Ts>...} ), Ts...>
  {};
}

namespace kyosu
{
  namespace _
  {
    template<typename T>
    using common_real = eve::as_floating_point_t<as_real_type_t<T>>;
  }

  //====================================================================================================================
  //! @brief Computes the best fitting Cayley-Dickson type from a series of types.
  //!
  //! @tparam Ts  Types used to compute the Cayley-Dickson underlying type.
  //====================================================================================================================
  template<typename... Ts>
  using as_cayley_dickson_t = typename as_cayley_dickson<Ts...>::type;

  template<auto Callable, typename... Ts>
  using expected_result_t = as_cayley_dickson_n_t < std::max( {dimension_v<Ts>...} )
                                                  , decltype( Callable( std::declval<as_real_type_t<Ts>>()...) )
                                                  >;

  using eve::as;

  //====================================================================================================================
  //! @struct as_real
  //! @brief Lightweight type-wrapper of real value type
  //!
  //! Wraps the real type associated to `T` into a constexpr, trivially constructible empty class to optimize passing
  //! type parameters via object instead of via template parameters.
  //!
  //! @tparam T Type to wrap
  //====================================================================================================================
  template<typename T>
  struct as_real : as<as_real_type_t<T>>
  {
    constexpr           as_real()          noexcept {}
    explicit constexpr  as_real(T const&)  noexcept {}
  };
  //====================================================================================================================
  //!  @}
  //====================================================================================================================


  //====================================================================================================================
  //! @struct complexify
  //! @brief compute the cayley dickson type associated to a floating type or any other type.
  //!
  //! if the type is an eve::floating_value return the complex type associated else let the type as is.
  //!
  //! @tparam T Type to wrap
  //====================================================================================================================
  template<typename T> struct complexify
  {
    using type = T;
  };

  template<eve::floating_value T> struct complexify<T>
  {
    using type = kyosu::as_cayley_dickson_n_t<2, T>;
  };

  template < typename T> using complexify_t =  typename complexify<T>::type;

  //====================================================================================================================
  //! @brief Compute the cayley_dickson_like type associated to a Cayley-Dickson-like family of types
  //!
  //! @tparam Ts Types used to compute the Cayley-Dickson_like common type.
  //====================================================================================================================

  template<typename... Ts>       struct as_cayley_dickson_like        : as_cayley_dickson<Ts...> {};

  template<concepts::real... Ts> struct as_cayley_dickson_like<Ts...> : eve::common_value<Ts...> {};
  template<typename... Ts> using as_cayley_dickson_like_t = typename as_cayley_dickson_like<Ts...>::type;

}
