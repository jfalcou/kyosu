//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL("Check polarpi", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  using w_t = eve::wide<e_t>;
  using c_t = kyosu::complex_t<e_t>;
  auto zer(e_t(0));
  auto wzer(w_t(0));
  auto o(e_t(1));
  auto wo(w_t(1));

  auto [r0, t0] = kyosu::to_polarpi(zer);
  TTS_EQUAL(r0, T{0});
  TTS_EQUAL(t0, T{0});

  auto [wr0, wt0] = kyosu::to_polarpi(wzer);
  TTS_EQUAL(wr0, w_t{0});
  TTS_EQUAL(wt0, w_t{0});

  {
    auto [r_1, t_1] = kyosu::to_polarpi(o, o);

    TTS_EQUAL(r_1, eve::sqrt_2(eve::as(r_1)));
    TTS_EQUAL(t_1, eve::quarter(eve::as(t_1)));

    auto [rc, tc] = kyosu::to_polarpi(c_t(1, 1));

    TTS_EQUAL(rc, eve::sqrt_2(eve::as(rc)));
    TTS_EQUAL(tc, eve::quarter(eve::as(tc)));

    auto [wr_1, wt_1] = kyosu::to_polarpi(wo, wo);
    TTS_EQUAL(wr_1, eve::sqrt_2(eve::as(wr_1)));
    TTS_EQUAL(wt_1, eve::quarter(eve::as(wt_1)));

    auto [wr_2, wt_2] = kyosu::to_polarpi(wo, o);
    TTS_EQUAL(wr_2, eve::sqrt_2(eve::as(wr_2)));
    TTS_EQUAL(wt_2, eve::quarter(eve::as(wt_2)));

    auto [wr_3, wt_3] = kyosu::to_polarpi(o, wo);
    TTS_EQUAL(wr_3, eve::sqrt_2(eve::as(wr_3)));
    TTS_EQUAL(wt_3, eve::quarter(eve::as(wt_3)));
  }
};
