//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright : KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/types/impl/quaternion/axis.hpp>
#include <kyosu/functions/to_quaternion.hpp>

namespace kyosu::tags
{
  struct callable_align : eve::elementwise
  {
    using callable_tag_type = callable_align;

    KYOSU_DEFERS_CALLABLE(align_);

    template<typename V,  typename  U, bool normalize>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V  v0
                                               , U  v1
                                                , _::norming<normalize>) noexcept
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

    template<typename V,  typename  U>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V  v0
                                               , U  v1) noexcept
    {
      auto fn = callable_align{};
      return fn(v0, v1, normalize);
    }

    template<typename T0, typename T1>
    KYOSU_FORCEINLINE auto operator()(T0 target0,
                                      T1 target1
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0,  target1))
    {
      return eve::tag_invoke(*this, target0,  target1);
    }

    template<typename T0, typename T1, bool normalize>
    KYOSU_FORCEINLINE auto operator()( T0 const& target0
                                     , T1 const& target1
                                     , _::norming<normalize>) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, _::norming<normalize>()))
    {
      return eve::tag_invoke(*this, target0, target1, _::norming<normalize>());
    }

    template<typename... T>
    eve::unsupported_call<callable_align(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var align
  //!
  //! @brief Callable object computing a quaternion from its angle_axis representation.
  //!
  //!  This function build an unitary quaternion from an angle value and a 3 dimensionnal axis vector
  //!
  //! **Defined in header**
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
  //!     auto align(auto angle,  auto axis, auto norming = normalize) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `v0` :  span of 3 elements
  //!  * `v1` :  span of 3 elements
  //!  * normalize : can be assume_normalized or normalize. In the second case axis is normalized.
  //!                if axis is already normalized use assume_normalized is more efficient.
  //!
  //! **Return value**
  //!
  //!   An unitaryquaternion value representing a rotation that align v0 to v1.
  //!
  //!   If v0 or v1 is a nullvector  the result is UB
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/align.cpp}
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_align align = {};
}
