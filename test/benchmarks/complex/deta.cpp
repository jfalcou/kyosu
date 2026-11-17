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

TTS_CASE_TPL("Benchmark complex deta", float, double)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;

  auto x = kyosu::bench::random<type>(-10, 10);
  auto deta1 = [](auto v) { return kyosu::deta(1u, v); };
  {
    kyosu::bench::benchmark _("complex<" + tts::as_text(tts::typename_<T>) + "> deta");
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar ", deta1, x);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide", deta1, x);
  }

  TTS_PASS("Benchmarks - SUCCESS");
};
