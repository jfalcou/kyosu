//==================================================================================================
/*
  KYOSU - Complex Without Complexes
  Copyright: KYOSU Project Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>

namespace kyosu
{
  template<typename Options>
  struct from_rotation_matrix_t : eve::elementwise_callable<from_rotation_matrix_t, Options>
  {
    template<typename M >
    KYOSU_FORCEINLINE constexpr auto operator()( M const& r) const noexcept
    //  -> quaternion_t<decltype(r[0][0])>
    {
      auto r11pr22 =  r[1][1] + r[2][2];
      auto qq0m1   =  r[0][0] + r11pr22;
      auto qq1m1   =  r[0][0] - r11pr22;
      auto r11mr22 =  r[1][1] - r[2][2];
      auto qq2m1   = -r[0][0] + r11mr22;
      auto qq3m1   = -r[0][0] - r11mr22;

      auto r21mr12 = r[2][1] - r[1][2];
      auto r02mr20 = r[0][2] - r[2][0];
      auto r10mr01 = r[1][0] - r[0][1];
      auto r01pr10 = r[1][0] + r[0][1];
      auto r20pr02 = r[2][0] + r[0][2];
      auto r12pr21 = r[1][2] + r[2][1];

      auto h = eve::half(eve::as(r11pr22));
      auto q0 =  eve::sqrt(eve::if_else(eve::is_gtz(qq0m1), eve::inc(qq0m1), (eve::sqr(r21mr12)+sqr(r02mr20)+eve::sqr(r10mr01))/(3-qq0m1)))*h;
      auto q1 =  eve::sqrt(eve::if_else(eve::is_gtz(qq1m1), eve::inc(qq1m1), (eve::sqr(r21mr12)+sqr(r01pr10)+eve::sqr(r20pr02))/(3-qq1m1)))*h;
      auto q2 =  eve::sqrt(eve::if_else(eve::is_gtz(qq2m1), eve::inc(qq2m1), (eve::sqr(r02mr20)+sqr(r01pr10)+eve::sqr(r12pr21))/(3-qq2m1)))*h;
      auto q3 =  eve::sqrt(eve::if_else(eve::is_gtz(qq3m1), eve::inc(qq3m1), (eve::sqr(r10mr01)+sqr(r20pr02)+eve::sqr(r12pr21))/(3-qq3m1)))*h;
      using e_t = decltype(r11pr22);
      return quaternion(q0, q1, q2, q3);
    }

    KYOSU_CALLABLE_OBJECT(from_rotation_matrix_t, from_rotation_matrix_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_rotation_matrix
  //!
  //! @brief Callable object computing a quaternion from its rotation_matrix representation.
  //!
  //!  This function returns a quaternion associated to the input rotation matrix m.
  //!  If m is not a proper 3x3 rotation matrix (i.e an orthogonal matrix with determinant 1)
  //!  the result is undefined.
  //!
  //! @groupheader{Header file}
  //!
  //!   @code
  //!   #include kyosu/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template < typename M >
  //!      auto from_rotation_matrix(auto m) const noexcept
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `m` the rotation matrix. The actual implementation assumes that m[i][j] will return
  //!        the ith line and jth column element of the matrix (indices starting from 0).
  //!
  //!
  //!   The computation method is inspired from the article: "Accurate Computation of
  //!   Quaternions from Rotation Matrices",  by   Soheil Sarabandi and Federico Thomas
  //!   Institut de Robotica i Informatica Industrial (CSIC-UPC)
  //!   Llorens Artigas 4-6, 08028 Barcelona, Spain.
  //!
  //! **Return value**
  //!
  //!    an unitary quaternion representing the rotation
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/from_rotation_matrix.cpp}
  //======================================================================================================================
  inline constexpr auto from_rotation_matrix = eve::functor<from_rotation_matrix_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
