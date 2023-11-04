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
  struct callable_cyl_seq: eve::elementwise
  {
    using callable_tag_type = callable_cyl_seq;

    KYOSU_DEFERS_CALLABLE(cyl_seq_);

    template<typename CB, eve::floating_ordered_value T, eve::detail::range Ra>
    static KYOSU_FORCEINLINE void deferred_call(auto, CB cb, int nn, T const& z, Ra & cbs) noexcept
    {
//       if (nn == 0) {
//         *std::begin(cbs) = cb(nn, z);
//         return;
//       }
//       size_t n = eve::abs(n);
//       auto rz = rec(z);
//       EVE_ASSERT(js.size() >= n+1, "js has not room enough");
//       auto rs = kyosu::_::R(n, z);
//       int i = n-1;

//       auto cur = std::rbegin(cbs);
//       *cur = cb(n, z);
//       while (i >= 0)
//       {
//         auto tmp = *cur;
//         --cur;
//         *cur = tmp*rs;
//         rs = 2*(i--)*rz-kyosu::rec(rs);
//       }
//       cur = std::begin(cbs);
//       if ( eve::is_ltz(nn)){
//         cur = ++std::begin(cbs);
//         for(size_t i=1; i <= n; i+= 2, std::advance(cur, 2)) *cur = -*cur;
//       }
    }

    template<typename CB, typename N, typename T, eve::detail::range Ra>
    KYOSU_FORCEINLINE auto operator()(CB f, N const & target0, T const& target1, Ra& target2) const noexcept
    -> decltype(eve::tag_invoke(*this, f, target0, target1, target2))
    {
      return eve::tag_invoke(*this, f, target0, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_cyl_seq(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_seq
//!   @brief Computes a sequence of bessel function values.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_seq(auto f, size_t n, T z, auto& cbs) noexcept;
//!      template<kyosu::concepts::complex>          constexpr auto cyl_seq(auto f, size_t n, T z, auto& cbs) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_seq(auto f, size_t n, T z, auto& cbs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * 'f':   any function of two parameters n and z which is a linear combination with constant coefficients
//!        of \f$J_n\f$ \f$Y_n\f$, \f$H_n^{(1)} or \f$ f$H_n^{(2)}\f$.
//!        If T is floating or complex f can be replaced by the evaluation f(n, z).
//!     * 'n':  positive integer.
//!     * `z`:   Value to process.
//!     * `cbs`: bidirectionnal range which will contain the output sequence \f$(f(i, z))_[i = 0, ..., n}\f$
//!
//!   **Return value**
//!
//!     * no return value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_seq.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cyl_seq cyl_seq = {};
}
