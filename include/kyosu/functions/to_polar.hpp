//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/abs.hpp>
#include <kyosu/functions/parts.hpp>
#include <kyosu/functions/pure.hpp>
#include <kyosu/functions/sign.hpp>
#include <kyosu/functions/arg.hpp>

namespace kyosu
{
  template<typename Options> struct to_polar_t : eve::elementwise_callable<to_polar_t, Options, raw_option, pedantic_option, radpi_option>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr kumi::tuple<as_real_type_t<Z>, as_real_type_t<Z>, Z> operator()(
      Z const& z) const noexcept
    requires(dimension_v<Z> > 2)
    {
      return KYOSU_CALL(z);
    }

    template<concepts::complex Z>
    KYOSU_FORCEINLINE constexpr kumi::tuple<as_real_type_t<Z>, as_real_type_t<Z>> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::real V> KYOSU_FORCEINLINE constexpr kumi::tuple<V, V> operator()(V v) const noexcept
    {
      return (*this)(complex(v));
    }

    template<concepts::real V, concepts::real W>
    KYOSU_FORCEINLINE constexpr kumi::tuple<eve::common_value_t<V, W>, eve::common_value_t<V, W>> operator()(
      V v, W w) const noexcept
    {
      using t_t = eve::common_value_t<V, W>;
      return (*this)(complex(t_t(v), t_t(w)));
    }

    KYOSU_CALLABLE_OBJECT(to_polar_t, to_polar_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var to_polar
  //!   @brief returns modulus and argument of the input.
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
  //!      //regular call
  //!      template<kyosu::concepts::cayley_dickson T>                             constexpr T to_polar(T z)      noexcept; //1
  //!      template<eve::floating_ordered_value T>                                 constexpr T to_polar(T z)      noexcept; //2
  //!      template<eve::floating_ordered_value T, eve::floating_ordered_value U)  constexpr T to_polar(T t, U u) noexcept; //3
  //!
  //!      // Semantic modifyiers
  //!      template<typenam T>                        constexpr T to_polar[radpi](/*any previous overload*/)      noexcept; //4
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to put in polar coordinates.
  //!
  //!   **Return value**
  //!
  //!     1. Returns  The kumi tuple `{rho, theta}`. for real and complex and `{rho, theta, I}` for other cayley-dickson
  //!        where \f$\textrm{I}\f$ is pure and \f$\textrm{I}^2 = -1 \f$.
  //!     2. same as to_polar(complex(z));
  //!     3. same as to_polar(complex(t, u));
  //!     4. If the `radpi` option is used the `theta` is given in \f$\pi\f$ multiples (rather than radians).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/to_polar.cpp}
  //======================================================================================================================
  inline constexpr auto to_polar = eve::functor<to_polar_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu
{
  namespace _
  {
    template<typename C, eve::callable_options O>
    KYOSU_FORCEINLINE constexpr auto to_polar_(KYOSU_DELAY(), O const& o, C c) noexcept
    {
      if constexpr (kyosu::concepts::complex<C>) return kumi::tuple{kyosu::abs(c), kyosu::arg[o](c)};
      else return kumi::tuple{kyosu::abs(c), kyosu::arg[o](c), sign(ipart(c)) * sign(pure(c))};
    }
  }
  inline constexpr auto to_polarpi = to_polar[radpi];
}
