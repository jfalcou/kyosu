//======================================================================================================================
/*
  Kyosu - Complex Math Made Easy
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL( "Check complex constructor from constants", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;
  auto spi  = T{3.1415};
  auto so   = T{1};
  auto wpi  = w_t(spi);
  auto wo   = w_t(so);

  kyosu::complex<T> z_sd{};
  TTS_EQUAL( get<0>(z_sd), T{0});
  TTS_EQUAL( get<1>(z_sd), T{0});

  kyosu::complex<T> z_s0{spi};
  TTS_EQUAL( get<0>(z_s0), spi );
  TTS_EQUAL( get<1>(z_s0), T{0});

  kyosu::complex<T> z_ss{spi,so};
  TTS_EQUAL( get<0>(z_ss), spi);
  TTS_EQUAL( get<1>(z_ss), so );

  eve::wide<kyosu::complex<T>>  z_vd{};
  TTS_EQUAL( get<0>(z_vd), w_t{0});
  TTS_EQUAL( get<1>(z_vd), w_t{0});

  eve::wide<kyosu::complex<T>>  z_vs{wo,spi};
  TTS_EQUAL( get<0>(z_vs), wo );
  TTS_EQUAL( get<1>(z_vs), wpi);

  eve::wide<kyosu::complex<T>>  z_sv{spi,wo};
  TTS_EQUAL( get<0>(z_sv), wpi);
  TTS_EQUAL( get<1>(z_sv), wo );

  eve::wide<kyosu::complex<T>>  z_vv{wo,wpi};
  TTS_EQUAL( get<0>(z_vv), wo );
  TTS_EQUAL( get<1>(z_vv), wpi);
};

TTS_CASE_TPL("Check complex constructor from lambda", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return T(1)/(1+i); };
  auto fill   = [](auto i, auto) { return kyosu::complex<T>(T(1+i),T(1)/(1+i)); };

  eve::wide<kyosu::complex<T>> z_l(fill);
  eve::wide<kyosu::complex<T>> z_ll(fill_r, fill_i);
  eve::wide<kyosu::complex<T>> z_lc(fill_r, T{1.25});
  eve::wide<kyosu::complex<T>> z_cl(T{8.8},fill_i);

  TTS_EQUAL( get<0>(z_l)  , w_t(fill_r));
  TTS_EQUAL( get<1>(z_l)  , w_t(fill_i));
  TTS_EQUAL( get<0>(z_ll) , w_t(fill_r));
  TTS_EQUAL( get<1>(z_ll) , w_t(fill_i));
  TTS_EQUAL( get<0>(z_lc) , w_t(fill_r));
  TTS_EQUAL( get<1>(z_lc) , w_t(1.25));
  TTS_EQUAL( get<0>(z_cl) , w_t(8.8));
  TTS_EQUAL( get<1>(z_cl) , w_t(fill_i));
};

TTS_CASE_TPL("Check complex copy/assignment", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;
  auto spi  = T{3.1415};
  auto so   = T{1};
  auto wpi  = w_t(spi);
  auto wo   = w_t(so);

  kyosu::complex<T> z_s{spi,so};
  auto              z_sc{z_s};
  kyosu::complex<T> z_sa;
  z_sa = z_s;

  eve::wide<kyosu::complex<T>>  z_v{wo,wpi};
  auto                          z_vc{z_v};
  eve::wide<kyosu::complex<T>>  z_va;
  z_va = z_v;

  TTS_EQUAL ( z_sc, z_s );
  TTS_EQUAL ( z_sa, z_s );
  TTS_EQUAL ( z_vc, z_v );
  TTS_EQUAL ( z_va, z_v );
};
