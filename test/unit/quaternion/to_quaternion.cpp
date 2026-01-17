//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL("Check to_quaternion converter from constants", kyosu::scalar_real_types)<typename T>(tts::type<T>)
{
  using e_t = T;
  using w_t = eve::wide<e_t>;
  using q_t = kyosu::quaternion_t<e_t>;
  using wq_t = eve::wide<kyosu::quaternion_t<e_t>>;
  auto zer(e_t(0));
  auto wzer(w_t(0));
  auto o(e_t(1));
  auto z(e_t(0));
  auto wo(w_t(1));
  auto wz(w_t(0));

  q_t z_0 = kyosu::quaternion(zer);
  TTS_EQUAL(get<0>(z_0), T{0});
  TTS_EQUAL(get<1>(z_0), T{0});
  TTS_EQUAL(get<2>(z_0), T{0});
  TTS_EQUAL(get<3>(z_0), T{0});

  wq_t wz_0 = kyosu::quaternion(wzer);
  TTS_EQUAL(get<0>(wz_0), w_t{0});
  TTS_EQUAL(get<1>(wz_0), w_t{0});
  TTS_EQUAL(get<2>(wz_0), w_t{0});
  TTS_EQUAL(get<3>(wz_0), w_t{0});

  {
    auto z_1 = kyosu::quaternion(o, o);

    TTS_EQUAL(get<0>(z_1), T(1));
    TTS_EQUAL(get<1>(z_1), T(1));
    TTS_EQUAL(get<2>(z_1), T(0));
    TTS_EQUAL(get<3>(z_1), T(0));

    wq_t wz_1 = kyosu::quaternion(wo, wo);
    TTS_EQUAL(get<0>(wz_1), wo);
    TTS_EQUAL(get<1>(wz_1), wo);
    TTS_EQUAL(get<2>(wz_1), wz);
    TTS_EQUAL(get<3>(wz_1), wz);

    wq_t wz_2 = kyosu::quaternion(wo, o, wo, o);
    TTS_EQUAL(get<0>(wz_2), wo);
    TTS_EQUAL(get<1>(wz_2), wo);
    TTS_EQUAL(get<2>(wz_2), wo);
    TTS_EQUAL(get<3>(wz_2), wo);

    wq_t wz_3 = kyosu::quaternion(o, wo, z, o);
    TTS_EQUAL(get<0>(wz_3), wo);
    TTS_EQUAL(get<1>(wz_3), wo);
    TTS_EQUAL(get<2>(wz_3), wz);
    TTS_EQUAL(get<3>(wz_3), wo);
  }

  using c_t = kyosu::complex_t<e_t>;
  auto zcc = kyosu::quaternion(c_t(1, 1), c_t(0, 1));

  TTS_EQUAL(get<0>(zcc), T(1));
  TTS_EQUAL(get<1>(zcc), T(1));
  TTS_EQUAL(get<2>(zcc), T(0));
  TTS_EQUAL(get<3>(zcc), T(1));

  auto zc = kyosu::quaternion(c_t(1, 1));

  TTS_EQUAL(get<0>(zc), T(1));
  TTS_EQUAL(get<1>(zc), T(1));
  TTS_EQUAL(get<2>(zc), T(0));
  TTS_EQUAL(get<3>(zc), T(0));
};
