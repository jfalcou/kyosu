//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

template <typename T>
auto prod(auto m,   std::array<T, 3> const & v)
{
  std::array<T, 3> r;
  for(size_t i=0; i < v.size(); ++i)
  {
    r[i] = m[i][0]*v[0]+m[i][1]*v[1]+m[i][2]*v[2];
  }
  return r;
}

TTS_CASE_WITH ( "Check behavior of to_rotation_matrix on wide"
              , kyosu::simd_real_types
              , tts::generate( tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t =  eve::element_type_t<T> ;
  using wq_t = eve::wide<kyosu::quaternion_t<e_t>, eve::cardinal_t<T>>;
  std::array<T, 3> v{T(1), T(2), T(3)};
  auto q = kyosu::sign(wq_t(a0, a1, a2, a3));
  wq_t qv(0, v[0], v[1], v[2]);
  auto m = kyosu::to_rotation_matrix[kyosu::assume_unitary](q);
  auto refq = q*qv*kyosu::conj(q);
  auto res  = prod(m, v);
  std::array<T, 3> ref{kyosu::ipart(refq), kyosu::jpart(refq), kyosu::kpart(refq)};
  for(int j=0; j <3 ; ++j)
  {
    TTS_RELATIVE_EQUAL(res[j], ref[j], 0.0002);
  }
  auto q1 = wq_t(a0, a1, a2, a3);
  auto m1 = kyosu::to_rotation_matrix(q1);
  auto res1  = prod(m1, v);
  for(int j=0; j <3 ; ++j)
  {
    TTS_RELATIVE_EQUAL(res1[j], ref[j], 0.0002);
  }
};
