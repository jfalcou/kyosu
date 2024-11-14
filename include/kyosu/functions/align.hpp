//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright: KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>
#include <kyosu/types/impl/quaternion/axis.hpp>

namespace kyosu
{
  template<typename Options>
  struct align_t : eve::elementwise_callable<align_t, Options>
  {

    template<concepts::real T, concepts::real U, std::size_t S, bool normalize>
    requires(S >= 3)
      KYOSU_FORCEINLINE constexpr auto operator()( std::span<T, S> v0
                                                 , std::span<U, S> v1
                                                , _::norming<normalize>) const noexcept
    {
      auto qv0 = quaternion(eve::zero(eve::as(v0[0])), v0[0], v0[1], v0[2]);
      auto qv1 = quaternion(eve::zero(eve::as(v1[0])), v1[0], v1[1], v1[2]);
      auto v1v0 = qv1*qv0;
      if constexpr(normalize)
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
  //!     auto align(auto v1, auto v2, auto norming) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `v0`:  span of 3 elements
  //!  * `v1`:  span of 3 elements
  //!  * norming: can be assume_normalized or normalize. In the second case axis is normalized.
  //!                if axis is already normalized use of assume_normalized is more efficient.
  //!
  //! **Return value**
  //!
  //!   An unitary quaternion value representing a rotation that align v0 to v1.
  //!   If v0 or v1 is a nullvector  the result is UB
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/align.cpp}
  //================================================================================================
  inline constexpr auto align = eve::functor<align_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
