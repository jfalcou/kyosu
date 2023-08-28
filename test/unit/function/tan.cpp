//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

#  if __has_include (<boost/math/quaternion.hpp>)
#    include <boost/math/quaternion.hpp>
#    define HAS_BOOST
#  endif

TTS_CASE_WITH ( "Check kyosu::tan over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(kyosu::tan(data), eve::tan(data), 0.5);
};

#ifdef HAS_BOOST

template < typename T >
auto cv(boost::math::quaternion<T> const &bq)
{
  return kyosu::quaternion<T>(bq.R_component_1(), bq.R_component_2(),
                              bq.R_component_3(), bq.R_component_4());
}

TTS_CASE_WITH ( "Check kyosu::tan over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using ke_t = kyosu::as_quaternion_t<T>;
  using bq_t = boost::math::quaternion<eve::element_type_t<T>>;
  auto boost_tan = [](auto x, auto y, auto z,  auto t){return cv(boost::math::tan(bq_t(x, y, z, t))); };
  ke_t e([&](auto n, auto){return boost_tan(r.get(n), i.get(n), j.get(n), k.get(n)); });
  auto q = ke_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::tan(q), e, 1e-5);
};
#  endif
