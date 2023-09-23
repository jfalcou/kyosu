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
  struct callable_rotate_vec : eve::elementwise
  {
    using callable_tag_type = callable_rotate_vec;

    KYOSU_DEFERS_CALLABLE(rotate_vec_);

    template<eve::floating_ordered_value V, eve::floating_ordered_value T, bool normalize>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const &
                                               , std::span<T, 3> const & v
                                               , _::norming<normalize>) noexcept
    {
      return v;
    }

    template<eve::floating_ordered_value V
             , eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const &
                                               , std::span<T, 3> const & v
                                               ) noexcept
    {
      return v;
    }

    template<typename T0, typename T1, bool normalize>
    KYOSU_FORCEINLINE auto operator()( T0 const& target0
                                     , T1 const& target1
                                     , _::norming<normalize>) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, _::norming<normalize>()))
    {
      return eve::tag_invoke(*this, target0, target1, _::norming<normalize>());
    }

    template<typename T0, typename T1>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0,
                                      T1 const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1, normalize);
    }

    template<typename... T>
    eve::unsupported_call<callable_rotate_vec(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var rotate_vec
  //!
  //! @brief Callable object rotating an \f$\mathbb{R}^3\f$ vector using a quaternion.
  //!
  //! **Defined in header**
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
  //!     auto rotate_vec( auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q`:   quaternion value defining the rotation.
  //!  `x`:   span of 3 elements to rotate
  //!
  //! **Return value**
  //!
  //!   the span rotated by q
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/rotate_vec.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_rotate_vec rotate_vec = {};
}
