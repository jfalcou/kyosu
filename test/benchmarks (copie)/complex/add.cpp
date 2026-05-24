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

TTS_CASE_TPL("Benchmark complex math", float, double)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;

  auto rnd_cmplx = [&]() {
    return std::complex<T>{::tts::random_value<T>(-100, 100), ::tts::random_value<T>(-100, 100)};
  };
  auto rnd_kyosu = [&]() { return type{::tts::random_value<T>(-100, 100), ::tts::random_value<T>(-100, 100)}; };

  {
    kyosu::bench::benchmark _("complex<" + tts::as_text(tts::typename_<T>) + "> op+");
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar", kyosu::add, rnd_kyosu, rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(
      _, std::complex<T>, "std::scalar", [](auto a, auto b) { return a + b; }, rnd_cmplx, rnd_cmplx);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide", kyosu::add, rnd_kyosu, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark _("complex<" + tts::as_text(tts::typename_<T>) + "> abs");
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar", kyosu::abs, rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, std::complex<T>, "std::scalar", [](auto a) { return std::abs(a); }, rnd_cmplx);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide", kyosu::abs, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark _("complex<" + tts::as_text(tts::typename_<T>) + "> sqrt");
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar", kyosu::sqrt, rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, std::complex<T>, "std::scalar", [](auto a) { return std::sqrt(a); }, rnd_cmplx);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide", kyosu::sqrt, rnd_kyosu);
  }

  TTS_PASS("Benchmarks - SUCCESS");
};
