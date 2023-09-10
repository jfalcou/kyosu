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
  struct callable_from_euler : eve::elementwise
  {
    using callable_tag_type = callable_from_euler;

    KYOSU_DEFERS_CALLABLE(from_euler_);

    template<eve::floating_ordered_value U,
             eve::floating_ordered_value V,
             eve::floating_ordered_value W, int I,  int J,  int K, bool Extrinsic>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , U const & v1
                                               , V const & v2
                                               , W const & v3
                                               , _::axis<I>
                                               , _::axis<J>
                                               , _::axis<K>
                                               , _::ext<Extrinsic>
                                               ) noexcept
    requires(I != J && J != K)
    {
      using e_t = decltype(v1+v2+v3);
      using q_t = decltype(to_quaternion(e_t{}));
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
    template<typename T0, typename T1, typename T2, int I,  int J,  int K, bool Extrinsic>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0,
                                      T1 const& target1,
                                      T2 const& target2
                                     , _::axis<I>
                                     , _::axis<J>
                                     , _::axis<K>
                                     , _::ext<Extrinsic>
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0,  target1,  target2
                               , _::axis<I>{}
                               , _::axis<J>{}
                               , _::axis<K>{}
                               , _::ext<Extrinsic>{}
                               ))
    {
      return eve::tag_invoke(*this, target0, target1, target2
                            , _::axis<I>{}
                            , _::axis<J>{}
                            , _::axis<K>{}
                            , _::ext<Extrinsic>{} );
    }

    template<typename... T>
    eve::unsupported_call<callable_from_euler(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_euler
  //!
  //! @brief Callable object computing a quaternion from its euler representation.
  //!
  //!  This function build euler angles from 3 euler angles in radian. Template parameters I, J, K of type int
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
  //!  * `a`, `b`, `c` : the angles in radian
  //!  * `a1`, `a2`, `a3` the axis parameters to be chosen between _X,  _Y, _Z (two consecutive axis cannot be the same)
  //!  * `e' : allows to choose between Extrinsic or Intrinsic representations.
  //!
  //!  **Template parameters**
  //!
  //!     * I, J, K : are on call deduced from the axis parameters
  //!
  //!
  //!   The computation method is taken from the article : "Quaternion to Euler angles conversion: A
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
  //! @godbolt{doc/quaternion/regular/from_euler.cpp}
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_from_euler from_euler = {};
}
