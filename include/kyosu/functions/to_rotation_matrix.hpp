//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright : KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/types/impl/quaternion/axes.hpp>
#include <kyosu/functions/to_quaternion.hpp>

namespace kyosu::tags
{
  struct callable_to_rotation_matrix : eve::elementwise
  {
    using callable_tag_type = callable_to_rotation_matrix;

    KYOSU_DEFERS_CALLABLE(to_rotation_matrix_);

    template<eve::floating_ordered_value V, bool normalize>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , [[maybe_unused]] V const & q
                                               , nor<normalize>) noexcept
    {
      if constexpr (!normalize) EVE_ASSERT(eve::all(kyosu::is_unitary(v)), "some quaternions are not unitary");
      using m_t = std::array< std::array<V, 3>, 3>;
      return m_t{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}} ;

    }

    template<eve::floating_ordered_value V>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & q) noexcept
    {
      return to_rotation_matrix(q, Assume_normalized);
    }

    template<typename T0, bool normalize>
    KYOSU_FORCEINLINE auto operator()(T0 target0,
                                      nor<normalize> target1
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0,  target1))
    {
      return eve::tag_invoke(*this, target0,  target1);
    }

    template<typename T0>
    KYOSU_FORCEINLINE auto operator()(T0 target0) const noexcept
    -> decltype(eve::tag_invoke(*this, target0,  Normalize))
    {
      return eve::tag_invoke(*this, target0,  Normalize);
    }

//     template<typename... T>
//     eve::unsupported_call<callable_to_rotation_matrix(T&&...)> operator()(T&&... x) const
//     requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_rotation_matrix
  //!
  //! @brief Callable object computing a quaternion from its to_rotation_matrix representation.
  //!
  //!  This function build rotation_matrix angles from a quaternion. Template parameters I, J, K of type int
  //!  are used to choose the rotation_matrix order.
  //!
  //!  for instance I = 3, J = 2, K = 3 choose the ZYZ sequence.
  //!  the values of I, J, and K must be in {1, 2, 3} ans satisfy I != J && J != K.
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
  //!       auto to_rotation_matrix(auto q) const noexcept;
  //!       auto to_rotation_matrix(auto q, Assume_normalized) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `q`  quaternion representing the rotation
  //!  * `Asume_normalized``: implies that q is already normalized
  //!
  //!
  //!
  //! **Return value**
  //!
  //!   compute the rotation matrix associated to the quaternion.
  //!
  //!   if T is the element type of q,  returns an std::array<std::array<T, 3>, 3> containing
  //!   the 9 coefficients of the rotation matrix
  //!
  //! @note use this function if you really need the rotation matrix,  but to rotate vectors
  //!       prefer the function rot_vec that directly uses the quaternion.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/quaternion/regular/to_rotation_matrix.cpp}
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_to_rotation_matrix to_rotation_matrix = {};
}
