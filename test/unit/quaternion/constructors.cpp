//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL("Check quaternion constructor from constants", kyosu::scalar_real_types)<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;
  auto spi = T{3.1415};
  auto so = T{1};
  auto wpi = w_t(spi);
  auto wo = w_t(so);

  kyosu::quaternion_t<T> z_sd{};
  kyosu::quaternion_t<T> z_s0{spi};
  kyosu::quaternion_t<T> z_ss{spi, so, so, so};
  eve::wide<kyosu::quaternion_t<T>> z_vd{};
  eve::wide<kyosu::quaternion_t<T>> z_vs{wo, spi, spi, spi};
  eve::wide<kyosu::quaternion_t<T>> z_sv{spi, wo, wo, wo};
  eve::wide<kyosu::quaternion_t<T>> z_vv{wo, wpi, wpi, wpi};

  // auto a = kumi::make_tuple(wpi,wpi,wpi);
  // eve::wide<kyosu::quaternion_t<T>> z_ra =  eve::quaternion(wo,a);

  TTS_EQUAL(get<0>(z_sd), T{0});
  TTS_EQUAL(get<1>(z_sd), T{0});
  TTS_EQUAL(get<2>(z_sd), T{0});
  TTS_EQUAL(get<3>(z_sd), T{0});

  TTS_EQUAL(get<0>(z_s0), spi);
  TTS_EQUAL(get<1>(z_s0), T{0});
  TTS_EQUAL(get<2>(z_s0), T{0});
  TTS_EQUAL(get<3>(z_s0), T{0});

  TTS_EQUAL(get<0>(z_ss), spi);
  TTS_EQUAL(get<1>(z_ss), so);
  TTS_EQUAL(get<2>(z_ss), so);
  TTS_EQUAL(get<3>(z_ss), so);

  TTS_EQUAL(get<0>(z_vd), w_t{0});
  TTS_EQUAL(get<1>(z_vd), w_t{0});
  TTS_EQUAL(get<2>(z_vd), w_t{0});
  TTS_EQUAL(get<3>(z_vd), w_t{0});

  TTS_EQUAL(get<0>(z_vs), wo);
  TTS_EQUAL(get<1>(z_vs), wpi);
  TTS_EQUAL(get<2>(z_vs), wpi);
  TTS_EQUAL(get<3>(z_vs), wpi);

  TTS_EQUAL(get<0>(z_sv), wpi);
  TTS_EQUAL(get<1>(z_sv), wo);
  TTS_EQUAL(get<2>(z_sv), wo);
  TTS_EQUAL(get<3>(z_sv), wo);

  TTS_EQUAL(get<0>(z_vv), wo);
  TTS_EQUAL(get<1>(z_vv), wpi);
  TTS_EQUAL(get<2>(z_vv), wpi);
  TTS_EQUAL(get<3>(z_vv), wpi);

  // TTS_EQUAL( get<0>(z_ra), wo );
  // TTS_EQUAL( get<1>(z_ra), wpi);
  // TTS_EQUAL( get<2>(z_ra), wpi);
  // TTS_EQUAL( get<3>(z_ra), wpi);
};

TTS_CASE_TPL("Check quaternion constructor from lambda", kyosu::scalar_real_types)<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;

  auto fill_r = [](auto i, auto) { return T(1 + i); };
  auto fill_i = [](auto i, auto) { return T(1) / (1 + i); };
  auto fill_j = [](auto i, auto) { return T(i); };
  auto fill_k = [](auto, auto) { return T(1); };
  auto fill = [](auto i, auto) { return kyosu::quaternion_t<T>(T(1 + i), T(1) / (1 + i), T(i), T(1)); };

  eve::wide<kyosu::quaternion_t<T>> z_l(fill);
  eve::wide<kyosu::quaternion_t<T>> z_ll(fill_r, fill_i, fill_j, fill_k);
  eve::wide<kyosu::quaternion_t<T>> z_lc(fill_r, T{1.25}, T{2.25}, T{3.25});
  eve::wide<kyosu::quaternion_t<T>> z_cl(T{8.8}, fill_i, T(1.0), fill_k);

  TTS_EQUAL(get<0>(z_l), w_t(fill_r));
  TTS_EQUAL(get<1>(z_l), w_t(fill_i));
  TTS_EQUAL(get<2>(z_l), w_t(fill_j));
  TTS_EQUAL(get<3>(z_l), w_t(fill_k));

  TTS_EQUAL(get<0>(z_ll), w_t(fill_r));
  TTS_EQUAL(get<1>(z_ll), w_t(fill_i));
  TTS_EQUAL(get<2>(z_ll), w_t(fill_j));
  TTS_EQUAL(get<3>(z_ll), w_t(fill_k));

  TTS_EQUAL(get<0>(z_lc), w_t(fill_r));
  TTS_EQUAL(get<1>(z_lc), w_t(1.25));
  TTS_EQUAL(get<2>(z_lc), w_t(2.25));
  TTS_EQUAL(get<3>(z_lc), w_t(3.25));

  TTS_EQUAL(get<0>(z_cl), w_t(8.8));
  TTS_EQUAL(get<1>(z_cl), w_t(fill_i));
  TTS_EQUAL(get<2>(z_cl), w_t(1.0));
  TTS_EQUAL(get<3>(z_cl), w_t(fill_k));
};

TTS_CASE_TPL("Check quaternion copy/assignment", kyosu::scalar_real_types)<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;
  auto spi = T{3.1415};
  auto so = T{1};
  auto wpi = w_t(spi);
  auto wo = w_t(so);

  kyosu::quaternion_t<T> z_s{spi, so, so, so};
  auto z_sc{z_s};
  kyosu::quaternion_t<T> z_sa;
  z_sa = z_s;

  eve::wide<kyosu::quaternion_t<T>> z_v{wo, wpi, wpi, wpi};
  auto z_vc{z_v};
  eve::wide<kyosu::quaternion_t<T>> z_va;
  z_va = z_v;

  TTS_EQUAL(z_sc, z_s);
  TTS_EQUAL(z_sa, z_s);
  TTS_EQUAL(z_vc, z_v);
  TTS_EQUAL(z_va, z_v);
};
