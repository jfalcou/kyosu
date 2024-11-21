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

TTS_CASE_WITH ( "Check kyosu::coth over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(kyosu::coth(data), eve::coth(data), 0.5);
};

#ifdef HAS_BOOST

template < typename T >
auto cv(boost::math::quaternion<T> const &bq)
{
  return kyosu::quaternion_t<T>(bq.R_component_1(), bq.R_component_2(),
                              bq.R_component_3(), bq.R_component_4());
}

TTS_CASE_WITH ( "Check kyosu::coth over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(1,3)
                              , tts::randoms(-3,3), tts::randoms(-3,3)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  auto prec = (sizeof(eve::element_type_t<T>) == 4) ? 1.0e-2 :tts::prec<T>();
  using ke_t = kyosu::quaternion_t<T>;
  using bq_t = boost::math::quaternion<eve::element_type_t<T>>;
  auto boost_coth = [](auto x, auto y, auto z,  auto t){return kyosu::rec(cv(boost::math::tanh(bq_t(x, y, z, t)))); };
  ke_t e([&](auto n, auto){return boost_coth(r.get(n), i.get(n), j.get(n), k.get(n)); });
  auto q = ke_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::coth(q), e, prec);
};
#  endif
