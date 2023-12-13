//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/bessel.hpp>

namespace kyosu::tags
{
  struct callable_cyl_bessel_i: eve::elementwise
  {
    using callable_tag_type = callable_cyl_bessel_i;

    KYOSU_DEFERS_CALLABLE(cyl_bessel_i_);

    template<eve::floating_scalar_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N nu, T const& v) noexcept
    {
      auto fnu = callable_cyl_bessel_i{};
      return fnu(nu, complex(v));
    }

    template<eve::floating_scalar_value N, eve::floating_ordered_value T, typename R>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N nu, T const& v, R& is) noexcept
    {
      auto fnu = callable_cyl_bessel_i{};
      return fnu(nu, complex(v), is);
    }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename N, typename T, typename R>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1, R & out0) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, out0))
    {
      return eve::tag_invoke(*this, target0, target1, out0);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_bessel_i(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_i
//!   @brief Computes the Modified Bessel functions of the first kind.
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
//!      template<eve::floating_ordered_value, kyosu::concepts::cayley_dickson T>
//!      constexpr auto cyl_bessel_i(N nu, T z) noexcept;
//!
//!      template<eve::floating_ordered_value, eve::floating_ordered_value T>
//!      constexpr T    cyl_bessel_i(N nu, T z) noexcept;
//!
//!      template<eve::floating_ordered_value, kyosu::concepts::cayley_dickson T, Range R>
//!      constexpr auto cyl_bessel_i(N nu, T z, R & is) noexcept;
//!
//!      template<eve::floating_ordered_value, eve::floating_ordered_value T, Range R>
//!      constexpr T    cyl_bessel_i(N nu, T z, R& is) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `nu`: order of the function.
//!     * `z`: Value to process.
//!     * `is`: Ouput range able to contain `n = int(abs(nu))+1` complex values (of type complex_t<T> or Z respectively)
//!
//!   **Return value**
//!
//!     * returns \f$I_\nu(z)\f$.
//!
//!   *Ouput values
//!
//!     * on output (if present) 1s contains the values of   \f$ (I^{(1)}_{\nu_0+\epsilon i})_{i = 0 \cdots n} \f$;
//!       where \f$ \nu_0 \f$ is the fractional part of \f$\nu\f$ and \f$\epsilon\f$ is the sign of  \f$ \nu\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_i.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_bessel_i cyl_bessel_i = {};
}
