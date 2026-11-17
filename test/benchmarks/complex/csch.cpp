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

TTS_CASE_TPL("Benchmark complex csch", float, double)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;

  auto x = kyosu::bench::random<type>(-10, 10);

  {
    kyosu::bench::benchmark _("complex<" + tts::as_text(tts::typename_<T>) + "> csch");
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar ", kyosu::csch, x);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide", kyosu::csch, x);
  }

  TTS_PASS("Benchmarks - SUCCESS");
};
