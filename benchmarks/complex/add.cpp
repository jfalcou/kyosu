#include <benchmark.hpp>
#include <kyosu/kyosu.hpp>
#include <random>
#include <complex>

TTS_CASE_TPL("Benchmark complex math", float, double)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;
  std::mt19937 rng(::tts::random_seed());
  std::uniform_real_distribution<T> dist(-100.0f, 100.0f);

  auto rnd_cmplx = [&]() { return std::complex<T>{dist(rng), dist(rng)}; };
  auto rnd_kyosu = [&]() { return type{dist(rng), dist(rng)}; };

  std::cout << "\n# Benchmarking for T = " << ::tts::typename_<type> << std::endl;

  {
    kyosu::bench::benchmark runner;
    runner.template run<std::complex<T>>(
            "STD   S-ADD", [](auto a, auto b) { return a + b; }, rnd_cmplx, rnd_cmplx)
      .template run<type>("KYOSU S-ADD", kyosu::add, rnd_kyosu, rnd_kyosu)
      .template run<eve::wide<type>>("KYOSU W-ADD", kyosu::add, rnd_kyosu, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark runner;
    runner.template run<std::complex<T>>(
            "STD   S-ABS", [](auto a) { return std::abs(a); }, rnd_cmplx)
      .template run<type>("KYOSU S-ABS", kyosu::abs, rnd_kyosu)
      .template run<eve::wide<type>>("KYOSU W-ABS", kyosu::abs, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark runner;
    runner.template run<std::complex<T>>(
            "STD   S-SQRT", [](auto a) { return std::sqrt(a); }, rnd_cmplx)
      .template run<type>("KYOSU S-SQRT", kyosu::sqrt, rnd_kyosu)
      .template run<eve::wide<type>>("KYOSU W-SQRT", kyosu::sqrt, rnd_kyosu);
  }

  TTS_PASS("Benchmarks - SUCCESS");
};
