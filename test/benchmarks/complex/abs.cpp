//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================

#include <benchmark.hpp>
#include <kyosu/kyosu.hpp>
#include <complex>

TTS_CASE_TPL("Benchmark complex abs", float, double)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;

  auto rnd_cmplx = [&]() { return std::complex<T>{::tts::random_value<T>(-10, 10), ::tts::random_value<T>(-10, 10)}; };
  auto rnd_kyosu = [&]() { return type{::tts::random_value<T>(-10, 10), ::tts::random_value<T>(-10, 10)}; };

  {
    kyosu::bench::benchmark _("complex<" + tts::as_text(tts::typename_<T>) + "> abs");
    TTS_RUN_BENCHMARK_TPL(_, std::complex<T>, "std", [](auto a) { return std::abs(a); }, rnd_cmplx);
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar ", kyosu::abs, rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar raw", kyosu::abs[kyosu::raw], rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar pedantic", kyosu::abs[kyosu::pedantic], rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar flat", kyosu::abs[kyosu::flat], rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide", kyosu::abs, rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide raw", kyosu::abs[kyosu::raw], rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide pedantic", kyosu::abs[kyosu::pedantic], rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide flat", kyosu::abs[kyosu::flat], rnd_kyosu);
  }

  TTS_PASS("Benchmarks - SUCCESS");
};
