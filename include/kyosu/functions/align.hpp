//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright: KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>
#include <kyosu/details/axis.hpp>

namespace kyosu
{
  template<typename Options>
  struct align_t : eve::elementwise_callable<align_t, Options, assume_unitary_option>
  {

    template<concepts::real T, concepts::real U, std::size_t S>
    requires(S >= 3)
      KYOSU_FORCEINLINE constexpr auto operator()( std::span<T, S> v0
                                                 , std::span<U, S> v1) const noexcept
    {
      auto qv0 = quaternion(eve::zero(eve::as(v0[0])), v0[0], v0[1], v0[2]);
      auto qv1 = quaternion(eve::zero(eve::as(v1[0])), v1[0], v1[1], v1[2]);
      auto v1v0 = qv1*qv0;
      if constexpr(!Options::contains(assume_unitary))
      {
        return sign(oneminus(sign(v1v0)));
      }
      else
      {
        return sign(oneminus(v1v0));
      }
    }

    KYOSU_CALLABLE_OBJECT(align_t, align_);
  };
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var align
  //!
  //! @brief Callable object computing an unitary quaternion value representing a rotation that align v0 to v1.
  //!
  //! @groupheader{Header file}
  //!
  //!   @code
  //!   #include kyosu/module/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace kyosu
  //!   {
  //!     auto align(auto v1, auto v2)                 const noexcept;
  //!     auto align[assume_unitary](auto v1, auto v2) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `v0`:  span of 3 elements
  //!  * `v1`:  span of 3 elements
  //!
   //! **Return value**
  //!
  //!   An unitary quaternion value representing a rotation that align `v0` to `v1`.
  //!   If `v0` or `v01` is a nullvector  the result is one as a quaternion.
  //!
  //!  @note  by default  `v0` and  `v1` are not assumed unitary (vectors of norm 1). If it is the case
  //!             the decorator `assume_unitary` can be used.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/align.cpp}
  //================================================================================================
  inline constexpr auto align = eve::functor<align_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
