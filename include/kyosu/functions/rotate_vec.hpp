//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright: KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>
#include <kyosu/functions/abs.hpp>
#include <kyosu/functions/arg.hpp>

namespace kyosu
{
  template<typename Options>
  struct rotate_vec_t : eve::elementwise_callable<rotate_vec_t, Options, assume_unitary_option>
  {

    template<concepts::cayley_dickson Z, concepts::real T, std::size_t S>
    requires(dimension_v<Z> <= 4)
      KYOSU_FORCEINLINE constexpr auto operator()(Z const& q,  std::span<T, S> v) const noexcept
    {
      using e_t = as_real_type_t<Z>;
      using v_t = decltype(v[0]+e_t());
      std::array<v_t, 3> w, wp;
      using a_t = decltype(kyosu::abs(q));
      a_t fac(2);
      if constexpr(!Options::contains(assume_unitary)) fac *= kyosu::rec(kyosu::sqr_abs(q));
      auto [r, i, j, k] = q;
      w[0] = eve::fma(r, v[0], eve::diff_of_prod(j, v[2], k, v[1]));
      w[1] = eve::fma(r, v[1], eve::diff_of_prod(k, v[0], i, v[2]));
      w[2] = eve::fma(r, v[2], eve::diff_of_prod(i, v[1], j, v[0]));

      wp[0] = eve::fam(v[0], fac, eve::diff_of_prod(j, w[2], k, w[1]));
      wp[1] = eve::fam(v[1], fac, eve::diff_of_prod(k, w[0], i, w[2]));
      wp[2] = eve::fam(v[2], fac, eve::diff_of_prod(i, w[1], j, w[0]));
      return wp;
    }

    KYOSU_CALLABLE_OBJECT(rotate_vec_t, rotate_vec_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var rotate_vec
  //!
  //! @brief Callable object rotating an \f$\mathbb{R}^3\f$ vector using a quaternion.
  //!
  //! @groupheader{Header file}
  //!
  //!   @code
  //!   #include eve/module/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!     auto rotate_vec(auto q, auto v) const noexcept;
  //!     auto rotate_vec[assume_unitary](auto q, auto v) const noexcept
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q`:   quaternion value defining the rotation.
  //!  `v`:   span of 3 elements to rotate.
  //!
  //! **Return value**
  //!
  //!   1. the span rotated by q
  //!   2.  with `assume_unitary`, assumes that `q` is already normalized
  //!
  //! #### Example
  //! @godbolt{doc/rotate_vec.cpp}
  //================================================================================================
  inline constexpr auto rotate_vec = eve::functor<rotate_vec_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
