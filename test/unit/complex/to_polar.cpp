//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL("Check to_complex converter from constants", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  using w_t = eve::wide<e_t>;
  using c_t = kyosu::complex_t<e_t>;
  auto zer(e_t(0));
  auto wzer(w_t(0));
  auto o(e_t(1));
  auto wo(w_t(1));

  auto [r0, t0] = kyosu::to_polar(zer);
  TTS_ULP_EQUAL(r0, T{0}, 0.5);
  TTS_ULP_EQUAL(t0, T{0}, 0.5);

  auto [wr0, wt0] = kyosu::to_polar(wzer);
  TTS_ULP_EQUAL(wr0, w_t{0}, 0.5);
  TTS_ULP_EQUAL(wt0, w_t{0}, 0.5);

  {
    auto [r_1, t_1] = kyosu::to_polar(o, o);

    TTS_ULP_EQUAL(r_1, eve::sqrt_2(eve::as(r_1)), 0.5);
    TTS_ULP_EQUAL(t_1, eve::pio_4(eve::as(t_1)), 0.5);

    auto [rc, tc] = kyosu::to_polar(c_t(1, 1));

    TTS_ULP_EQUAL(rc, eve::sqrt_2(eve::as(rc)), 0.5);
    TTS_ULP_EQUAL(tc, eve::pio_4(eve::as(tc)), 0.5);

    auto [wr_1, wt_1] = kyosu::to_polar(wo, wo);
    TTS_ULP_EQUAL(wr_1, eve::sqrt_2(eve::as(wr_1)), 0.5);
    TTS_ULP_EQUAL(wt_1, eve::pio_4(eve::as(wt_1)), 0.5);

    auto [wr_2, wt_2] = kyosu::to_polar(wo, o);
    TTS_ULP_EQUAL(wr_2, eve::sqrt_2(eve::as(wr_2)), 0.5);
    TTS_ULP_EQUAL(wt_2, eve::pio_4(eve::as(wt_2)), 0.5);

    auto [wr_3, wt_3] = kyosu::to_polar(o, wo);
    TTS_ULP_EQUAL(wr_3, eve::sqrt_2(eve::as(wr_3)), 0.5);
    TTS_ULP_EQUAL(wt_3, eve::pio_4(eve::as(wt_3)), 0.5);
  }
};
