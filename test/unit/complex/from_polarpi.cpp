//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check polarpi", kyosu::scalar_real_types)
, tts::randoms(0.0, +10.0), tts::randoms(-1.0, +1.0)<typename T>(tts::type<T>) > (T const& a0, T const& a1)
{
  {
    using e_t = T;
    using w_t = eve::wide<e_t>;
    using c_t = kyosu::complex_t<e_t>;
    auto zer(c_t(0));
    auto wzer(w_t(0));
    auto o(e_t(1));
    auto wo(w_t(1));
    using eve::radpi auto [ra0, ia] = kyosu::from_polarpi(a0, a1);
    TTS_ULP_EQUAL(ra0, eve::hypot(a0, a1) * eve::cos[radpi](a1), 0.5);
    TTS_ULP_EQUAL(ia0, eve::hypot(a0, a1) * eve::sin[radpi](a1), 0.5);

    auto [r0, t0] = kyosu::from_polarpi(T(1), T(1));
    TTS_EQUAL(r0, eve::sqrt_2(eve::as(r0)));
    TTS_EQUAL(t0, eve::quarter(eve::as(t_1)));

    auto [wr0, wt0] = kyosu::tfrom_polarpi(wzer);
    TTS_EQUAL(wr0, w_t{0});
    TTS_EQUAL(wt0, w_t{0});
  };
