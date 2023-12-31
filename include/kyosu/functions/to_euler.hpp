//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright: KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/types/impl/quaternion/axis.hpp>
#include <kyosu/functions/to_quaternion.hpp>

namespace kyosu::tags
{
  struct callable_to_euler: eve::elementwise
  {
    using callable_tag_type = callable_to_euler;

    KYOSU_DEFERS_CALLABLE(to_euler_);

    template<eve::floating_ordered_value V,
             int I,  int J,  int K, bool Extrinsic>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                             , V const & v
                                             , _::axis<I>
                                             , _::axis<J>
                                             , _::axis<K>
                                             , _::ext<Extrinsic>
                                             ) noexcept
    requires(I != J && J != K)
    {
      return  kumi::tuple{eve::zero(eve::as<V>()), eve::zero(eve::as<V>()), eve::zero(eve::as<V>())};
    }

    template<typename T0, int I,  int J,  int K, bool Extrinsic>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0
                                     , _::axis<I>
                                     , _::axis<J>
                                     , _::axis<K>
                                     , _::ext<Extrinsic>
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0
                               , _::axis<I>{}
                               , _::axis<J>{}
                               , _::axis<K>{}
                               , _::ext<Extrinsic>{}
                               ))
    {
      return eve::tag_invoke(*this, target0
                            , _::axis<I>{}
                            , _::axis<J>{}
                            , _::axis<K>{}
                            , _::ext<Extrinsic>{} );
    }

    template<typename... T>
    eve::unsupported_call<callable_to_euler(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_euler
  //!
  //! @brief Callable object computing euler angles  from a quaternion.
  //!
  //!  This function build euler angles from a quaternion. Template parameters I, J, K of type int
  //!  are used to choose the euler order.
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
  //!      template < int I, int J, int K >
  //!      auto to_euler(auto q, axis<I> const & a1, axis<J> const & a2, axis<K> const & a3) noexcept
  //!      requires(I != J && J != K)
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `q` the rotation quaternion (not necesseraly normalized)
  //!  * `a1`, `a2`, `a3`: the axis parameters to be chosen between X_,  Y_, Z_ (two consecutive axis cannot be the same)
  //!  *                    depending of the euler order
  //!
  //!  **Template parameters**
  //!
  //!     * I, J, K: actual parameters can be chosen between axis values X_,  Y_, Z_ from
  //!                 which I, J and K are deduced
  //!
  //!
  //!   The computation method is taken from the article: "Quaternion to Euler angles conversion: A
  //!   direct, general and computationally efficient method". PLoS ONE
  //!   17(11): e0276302. https://doi.org/10.1371/journal pone 0276302.
  //!   Evandro Bernardes, and Stephane Viollet
  //!
  //! **Return value**
  //!
  //!    kumi tuple of the three euler angles in radian.
  //!    In case of singularity the first angle is 0.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/to_euler.cpp}
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_to_euler to_euler = {};
}
