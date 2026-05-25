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

TTS_CASE_TPL("Benchmark complex ldiv", float, double)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;

  auto rnd_kyosu = [&]() { return type{::tts::random_value<T>(-10, 10), ::tts::random_value<T>(-10, 10)}; };

  {
    kyosu::bench::benchmark _("complex<" + tts::as_text(tts::typename_<T>) + "> ldiv");
    TTS_RUN_BENCHMARK_TPL(_, type, "kyosu::scalar ", kyosu::ldiv, rnd_kyosu, rnd_kyosu);
    TTS_RUN_BENCHMARK_TPL(_, eve::wide<type>, "kyosu::wide", kyosu::ldiv, rnd_kyosu, rnd_kyosu);
  }

  TTS_PASS("Benchmarks - SUCCESS");
};
