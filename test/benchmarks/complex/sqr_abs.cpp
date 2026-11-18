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

TTS_CASE_TPL("Benchmark complex sqr_abs", float, double)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;

  auto x = kyosu::bench::random<type>(-10, 10);

  {
    kyosu::bench::benchmark _("complex<" + tts::as_text(tts::typename_<T>) + "> sqr_abs");
    TTS_RUN_BENCHMARK_TPL(_, std::complex<T>, "std", [](auto a) { return std::norm(a); }, x);
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar ", kyosu::sqr_abs, x);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide", kyosu::sqr_abs, x);
  }

  TTS_PASS("Benchmarks - SUCCESS");
};
