//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

#if __has_include(<boost/math/quaternion.hpp>)
#include <boost/math/quaternion.hpp>
#define HAS_BOOST
#endif

TTS_CASE_WITH("Check kyosu::sech over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_ULP_EQUAL(kyosu::sech(data), eve::sech(data), 0.5);
};

#ifdef HAS_BOOST

template<typename T> auto cv(boost::math::quaternion<T> const& bq)
{
  return kyosu::quaternion_t<T>(bq.R_component_1(), bq.R_component_2(), bq.R_component_3(), bq.R_component_4());
}

TTS_CASE_WITH("Check kyosu::sech over quaternion",
              kyosu::simd_real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r, T i, T j, T k)
{
  using ke_t = kyosu::quaternion_t<T>;
  using bq_t = boost::math::quaternion<eve::element_type_t<T>>;
  auto boost_sech = [](auto x, auto y, auto z, auto t) { return kyosu::rec(cv(boost::math::cosh(bq_t(x, y, z, t)))); };
  ke_t e([&](auto n, auto) { return boost_sech(r.get(n), i.get(n), j.get(n), k.get(n)); });
  auto q = ke_t(r, i, j, k);
  TTS_RELATIVE_EQUAL(kyosu::sech(q), e, tts::prec<T>());
};
#endif
