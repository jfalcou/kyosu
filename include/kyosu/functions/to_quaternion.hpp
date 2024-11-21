//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/types/quaternion.hpp>
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct make_quaternion_t : eve::callable<make_quaternion_t, Options>
  {
    template<concepts::quaternion Q>
    KYOSU_FORCEINLINE constexpr Q operator()(Q const& q) const noexcept
    {
      return KYOSU_CALL(q);
    }

    template<concepts::complex... Zs>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_n_t<4,as_real_type_t<Zs>...> operator()(Zs const&... zs) const noexcept
    requires(sizeof...(Zs) <= 2 && std::has_single_bit(sizeof...(Zs)))
    {
      return KYOSU_CALL(zs...);
    }

    template<eve::floating_value... Ts>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_n_t<4,Ts...> operator()(Ts... vs)  const noexcept
    requires(sizeof...(Ts) <= 4 && std::has_single_bit(sizeof...(Ts)))
    {
      return KYOSU_CALL(vs...);
    }

    KYOSU_CALLABLE_OBJECT(make_quaternion_t, make_quaternion_);
  };

  //====================================================================================================================
  //! @addtogroup functions
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //!   @var quaternion
  //!   @brief Constructs a kyosu::quaternion_t instance
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
  //!      template<eve::floating_value T> constexpr auto quaternion(T r, T i = 0, T j = 0, T k = 0)       noexcept;
  //!      template<eve::floating_value T> constexpr auto quaternion(complex_t<T> c0, complex_t<T> c1 = 0)  noexcept;
  //!      template<kyosu::concepts::cayley_dickson T> constexpr T quaternion(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`                : Quaternion value.
  //!     * `c0 `,`c1`         : Complex values generates the quaternion c0+j*conj(c1) i.e.
  //!                            real(c0+i*imag(c1)+j*real(1)+k*imag(c1)
  //!     * `r`, `i`, `j`, `k` : Real and unreal parts sued to construct a @ref kyosu::quaternion from its components
  //!
  //!   **Return value**
  //!
  //!   Returns a @ref kyosu::quaternion constructed from its arguments.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/to_quaternion.cpp}
  //====================================================================================================================

  inline constexpr auto quaternion = eve::functor<make_quaternion_t>;
  //====================================================================================================================
  //! @}
  //====================================================================================================================
}

namespace kyosu::_
{
  template<typename T, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto make_quaternion_(KYOSU_DELAY(), O const&, T v) noexcept
  {
    if      constexpr(eve::floating_value<T>) return as_cayley_dickson_n_t<4,T>(v, T{0}, T{0}, T{0});
    else if constexpr(concepts::complex<T>  ) return quaternion(get<0>(v), get<1>(v));
    else                                      return v;
  }

  template<typename T0, typename T1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto make_quaternion_(KYOSU_DELAY(), O const&, T0 v0, T1 v1) noexcept
  {
    if constexpr(concepts::complex<T0>) return quaternion(get<0>(v0),get<1>(v0),get<0>(v1), get<1>(v1));
    else                                return as_cayley_dickson_n_t<4,T0,T1,T0,T0>{v0,v1,T0{0},T0{0}};
  }

  template<typename T0, typename T1, typename T2, typename T3, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto make_quaternion_(KYOSU_DELAY(), O const&, T0 v0, T1 v1, T2 v2, T3 v3) noexcept
  {
    return as_cayley_dickson_n_t<4,T0,T1,T2,T3>{v0,v1,v2,v3};
  }
}
