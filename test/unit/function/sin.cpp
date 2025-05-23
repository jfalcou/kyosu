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


TTS_CASE_WITH ( "Check kyosu::sin over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T data)
{
  TTS_ULP_EQUAL(kyosu::sin(data), eve::sin(data), 0.5);
  auto cond = eve::is_ltz(data);

  TTS_RELATIVE_EQUAL(kyosu::sin[cond](data), kyosu::if_else(cond,  kyosu::sin(data), data), tts::prec<T>());
};

#ifdef HAS_BOOST

template < typename T >
auto cv(boost::math::quaternion<T> const &bq)
{
  return kyosu::quaternion_t<T>(bq.R_component_1(), bq.R_component_2(),
                              bq.R_component_3(), bq.R_component_4());
}

TTS_CASE_WITH ( "Check kyosu::sin over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-5,5), tts::randoms(-5,5)
                              , tts::randoms(-5,5), tts::randoms(-5,5)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using ke_t = kyosu::quaternion_t<T>;
  using bq_t = boost::math::quaternion<eve::element_type_t<T>>;
  auto boost_sin = [](auto x, auto y, auto z,  auto t){return cv(boost::math::sin(bq_t(x, y, z, t))); };
  ke_t e([&](auto n, auto){return boost_sin(r.get(n), i.get(n), j.get(n), k.get(n)); });
  auto q = ke_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::sin(q), e, tts::prec<T>());
};
#  endif
