#include <benchmark.hpp>
#include <kyosu/kyosu.hpp>
#include <random>
#include <complex>

TTS_CASE_TPL("Benchmark complex add", float, double)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;
  std::mt19937 rng(::tts::random_seed());
  std::uniform_real_distribution<T> dist(-100.0f, 100.0f);

  auto rnd_cmplx = [&]() { return std::complex<T>{dist(rng), dist(rng)}; };
  auto rnd_kyosu = [&]() { return type{dist(rng), dist(rng)}; };

  kyosu::bench::benchmark runner(4096, 2000);

  std::cout << "# Benchmarking for T = " << ::tts::typename_<type> << std::endl;

  runner.template run<std::complex<T>>(
          "STD C-ADD (SCALAR)", [](auto a, auto b) { return a + b; }, rnd_cmplx, rnd_cmplx)
    .template run<type>("KYOSU C-ADD (SCALAR)", kyosu::add, rnd_kyosu, rnd_kyosu)
    .template run<eve::wide<type>>("KYOSU ADD (SIMD)", kyosu::add, rnd_kyosu, rnd_kyosu);

  TTS_PASS("Benchmarks - SUCCESS");
};
