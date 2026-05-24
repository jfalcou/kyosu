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

TTS_CASE_TPL("Benchmark complex tanh", float, double)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;

  auto rnd_cmplx = [&]() { return std::complex<T>{::tts::random_value<T>(-10, 10), ::tts::random_value<T>(-10, 10)}; };
  auto rnd_kyosu = [&]() { return type{::tts::random_value<T>(-10, 10), ::tts::random_value<T>(-10, 10)}; };

  {
    kyosu::bench::benchmark _("complex<" + tts::as_text(tts::typename_<T>) + "> tanh");
    TTS_RUN_BENCHMARK_TPL(_, std::complex<T>, "std", [](auto a) { return std::tanh(a); }, rnd_cmplx);
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar ", kyosu::tanh, rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide", kyosu::tanh, rnd_kyosu);
  }

  TTS_PASS("Benchmarks - SUCCESS");
};
