//==================================================================================================
/*
  KYOSU - Complex Without Complexes
  Copyright: KYOSU Project Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>
#include <kyosu/types/impl/quaternion/axis.hpp>

namespace kyosu
{
  template<typename Options>
  struct from_euler_t : eve::elementwise_callable<from_euler_t, Options>
  {
    template<concepts::real U,
             concepts::real V,
             concepts::real W, int I,  int J, int K, bool Extrinsic>
    KYOSU_FORCEINLINE constexpr auto operator()( U const & v1
                                               , V const & v2
                                               , W const & v3
                                               , _::axis<I>
                                               , _::axis<J>
                                               , _::axis<K>
                                               , _::ext<Extrinsic>) const noexcept
    -> quaternion_t<eve::common_value_t<U, V, W>>
    requires(I != J && J != K)
    {
      using e_t = decltype(v1+v2+v3);
      using q_t = decltype(quaternion(e_t{}));
      auto h = eve::half(eve::as<e_t>());
      std::array<q_t, 3> qs;
      auto [sa, ca] = eve::sincos(v3*h);
      auto [sb, cb] = eve::sincos(v2*h);
      auto [sc, cc] = eve::sincos(v1*h);
      get<0>(qs[0]) = ca;
      get<0>(qs[1]) = cb;
      get<J>(qs[1]) = sb;
      get<0>(qs[2]) = cc;
      if constexpr(!Extrinsic)
      {
        get<K>(qs[0]) = sa;
        get<I>(qs[2]) = sc;
        q_t q = qs[2]*qs[1]*qs[0];
        return q;
      }
      else
      {
        get<I>(qs[0]) = sa;
        get<K>(qs[2]) = sc;
        q_t q = qs[0]*qs[1]*qs[2];
        return q;
      }
    }

    KYOSU_CALLABLE_OBJECT(from_euler_t, from_euler_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_euler
  //!
  //! @brief Callable object computing a quaternion from its euler representation.
  //!
  //!  This function builds a quaternion from 3 euler angles in radian. Template parameters I, J, K of type int
  //!  are used to choose the euler axis order.
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
  //!      template < int I, int J, int K > auto from_euler(auto a, auto b, auto c
  //!                                                      , axis<I> a1, axis<J> a2, axis<K> a3
  //!                                                      , ext e
  //!                                                      ) const noexcept;
  //!      requires(I != J && J != K)
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `a`, `b`, `c`: the angles in radian
  //!  * `a1`, `a2`, `a3` the axis parameters to be chosen between X_,  Y_, Z_ (two consecutive axis cannot be the same)
  //!  * `e': allows to choose between extrinsic or intrinsic representations.
  //!
  //!  **Template parameters**
  //!
  //!     * I, J, K: are on call deduced from the axis parameters
  //!
  //!
  //!   The computation method is taken from the article: "Quaternion to Euler angles conversion: A
  //!   direct, general and computationally efficient method". PLoS ONE
  //!   17(11): e0276302. https://doi.org/10.1371/journal pone 0276302.
  //!   Evandro Bernardes, and Stephane Viollet
  //!
  //! **Return value**
  //!
  //!    quaternion representing the rotation
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/from_euler.cpp}
  //======================================================================================================================
  inline constexpr auto from_euler = eve::functor<from_euler_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
