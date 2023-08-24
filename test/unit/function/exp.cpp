//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <boost/math/quaternion.hpp>

template < typename T >
auto cv(boost::math::quaternion<T> const &bq)
{
  return kyosu::quaternion<T>(bq.R_component_1(), bq.R_component_2(),
                              bq.R_component_3(), bq.R_component_4());
}

TTS_CASE_WITH ( "Check kyosu::exp over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(kyosu::exp(data), eve::exp(data), 0.5);
};


TTS_CASE_WITH ( "Check kyosu::exp over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using ke_t = kyosu::as_quaternion_t<T>;
  using bq_t = boost::math::quaternion<eve::element_type_t<T>>;
  auto boost_exp = [](auto x, auto y, auto z,  auto t){return cv(boost::math::exp(bq_t(x, y, z, t))); };
  ke_t e([&](auto n, auto){return boost_exp(r.get(n), i.get(n), j.get(n), k.get(n)); });
  auto q = ke_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::exp(q), e, 1e-5);
};
