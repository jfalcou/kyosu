//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options> struct convert_t : eve::callable<convert_t, Options>
  {
    template<concepts::cayley_dickson V, concepts::scalar_cayley_dickson Tgt>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<Tgt, V> operator()(V v, as<Tgt> tgt) const noexcept
    requires(dimension_v<V> <= dimension_v<Tgt>)
    {
      return KYOSU_CALL(v, tgt);
    }

    template<concepts::real V, concepts::scalar_cayley_dickson Tgt>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<Tgt, V> operator()(V v, as<Tgt> tgt) const noexcept
    {
      return KYOSU_CALL(v, tgt);
    }

    template<concepts::real V, concepts::scalar_real Tgt>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<Tgt, V> operator()(V v, as<Tgt> tgt) const noexcept
    {
      return KYOSU_CALL(v, tgt);
    }

    KYOSU_CALLABLE_OBJECT(convert_t, convert_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var convert
  //!   @brief convert to a target type
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
  //!     template<eve::scalar_value U> constexpr auto convert(auto x, eve::as<U> ) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameter**
  //!     * `x`: floating or Cayley Dickinson value to process.
  //!
  //!   **Template Parameter**
  //!     * `U`: target type to convert to.
  //!
  //!   **Return value**
  //!
  //!   The value resulting of the conversion of each of its elements to type U.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/convert.cpp}
  //======================================================================================================================
  inline constexpr auto convert = eve::functor<convert_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename T, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto convert_(KYOSU_DELAY(), O const&, T const& v, as<Z>) noexcept
  {
    if constexpr (std::same_as<T, Z>) return v;
    else if constexpr (concepts::cayley_dickson<Z>)
    {
      using type = eve::as_wide_as_t<Z, T>;
      if constexpr (dimension_v<T> == 1ULL) return type{eve::convert(v, eve::as<as_real_type_t<Z>>{})};
      else
      {
        using u_t = as_real_type_t<Z>;
        return kumi::apply([](auto const&... e) { return type{kyosu::convert(e, eve::as<u_t>{})...}; }, v);
      }
    }
    else return eve::convert(v, eve::as<Z>{});
  }
}
