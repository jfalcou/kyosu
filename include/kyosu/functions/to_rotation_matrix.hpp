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
  struct to_rotation_matrix_t : eve::elementwise_callable<to_rotation_matrix_t, Options, assume_unitary_option>
  {
    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr auto operator()(V const&) const noexcept
    {
      using m_t = std::array< std::array<V, 3>, 3>;
      return m_t{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    }

    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto operator()(Z  q) const noexcept
    requires(dimension_v<Z> <= 4)
    {
      if constexpr(!Options::contains(assume_unitary)) q = sign(q);
      using e_t = as_real_type_t<Z>;
      using m_t = std::array< std::array<e_t, 3>, 3>;
      if constexpr(kyosu::concepts::complex<Z>)
      {
        auto q0 = real(q);
        auto q1 = imag(q);
        auto q02 = 2*sqr(q0)-1;
        auto q0q1= 2*q0*q1;
        return m_t{{1, 0, 0}, {0, q02, -q0q1}, {0, q0q1, q02}};
      }
      else
      {
        auto q0 = real(q);
        auto q1 = ipart(q);
        auto q2 = jpart(q);
        auto q3 = kpart(q);

        // First row of the rotation matrix
        auto r00 = 2 * (sqr(q0) + sqr(q1)) - 1;
        auto r01 = 2 * (q1 * q2 - q0 * q3);
        auto r02 = 2 * (q1 * q3 + q0 * q2);

        // Second row of the rotation matrix
        auto r10 = 2 * (q1 * q2 + q0 * q3);
        auto r11 = 2 * (sqr(q0) + sqr(q2)) - 1;
        auto r12 = 2 * (q2 * q3 - q0 * q1);

        // Third row of the rotation matrix
        auto r20 = 2 * (q1 * q3 - q0 * q2);
        auto r21 = 2 * (q2 * q3 + q0 * q1);
        auto r22 = 2 * (sqr(q0) + sqr(q3)) - 1;

        // 3x3 rotation matrix
        using e_t = std::decay_t<decltype(q0)>;
        using l_t = std::array<e_t, 3>;
        using m_t = std::array<l_t, 3>;
        std::array<e_t, 3> l1{r00, r01, r02};
        std::array<e_t, 3> l2{r10, r11, r12};
        std::array<e_t, 3> l3{r20, r21, r22};
        return m_t{l1, l2, l3};
      }
    }

    KYOSU_CALLABLE_OBJECT(to_rotation_matrix_t, to_rotation_matrix_);
  };


  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_rotation_matrix
  //!
  //! @brief Callable object computing a quaternion from its to_rotation_matrix representation.
  //!
  //!  This function build rotation_matrix angles from a quaternion.
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
  //!       auto to_rotation_matrix(auto q) const noexcept;
  //!       auto to_rotation_matrix[assume_unitary](auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `q`  quaternion representing the rotation
  //!  * `assume_unitary`: assumes that q is already normalized
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
  //! @godbolt{doc/to_rotation_matrix.cpp}
  //================================================================================================
  inline constexpr auto to_rotation_matrix = eve::functor<to_rotation_matrix_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
