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

TTS_CASE_TPL("Benchmark complex powm1", float, double)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;

  auto x = kyosu::bench::random<type>(-10, 10);
  auto y = kyosu::bench::random<type>(-10, 10);

  {
    kyosu::bench::benchmark _("complex<" + tts::as_text(tts::typename_<T>) + "> powm1");
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar ", kyosu::powm1, x, y);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide", kyosu::powm1, x, y);
  }

  TTS_PASS("Benchmarks - SUCCESS");
};
