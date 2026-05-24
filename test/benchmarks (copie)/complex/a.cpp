#include <benchmark.hpp>
#include <kyosu/kyosu.hpp>
#include <random>
#include <complex>

TTS_CASE_TPL("Benchmark complex math", float)
<typename T>(tts::type<T>)
{
  using type = kyosu::complex_t<T>;
  std::mt19937 rng(::tts::random_seed());
  std::uniform_real_distribution<T> dist(-10.0f, 10.0f);

  auto rnd_cmplx = [&]() { return std::complex<T>{dist(rng), dist(rng)}; };
  auto rnd_kyosu = [&]() { return type{dist(rng), dist(rng)}; };

  std::cout << "\n# Benchmarking for T = " << ::tts::typename_<type> << " - Target architecture: " << eve::current_api
            << "\n"
            << std::endl;

  {
    kyosu::bench::benchmark runner;
    runner.template run<type>("KYOSU S-ABS", kyosu::abs, rnd_kyosu)
      .template run<std::complex<T>>(
        "STD   S-ABS", [](auto a) { return std::abs(a); }, rnd_cmplx)
      .template run<eve::wide<type>>("KYOSU W-ABS", kyosu::abs, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark runner;
    runner.template run<type>("KYOSU S-ACOS", kyosu::acos, rnd_kyosu)
      .template run<std::complex<T>>(
        "STD   S-ACOS", [](auto a) { return std::acos(a); }, rnd_cmplx)
      .template run<eve::wide<type>>("KYOSU W-ACOS", kyosu::acos, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark runner;
    runner.template run<type>("KYOSU S-ACOSH", kyosu::acosh, rnd_kyosu)
      .template run<std::complex<T>>(
        "STD   S-ACOSH", [](auto a) { return std::acosh(a); }, rnd_cmplx)
      .template run<eve::wide<type>>("KYOSU W-ACOSH", kyosu::acosh, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark runner;
    runner.template run<type>("KYOSU S-ADD", kyosu::add, rnd_kyosu, rnd_kyosu)
      .template run<std::complex<T>>(
        "STD   S-ADD", [](auto a, auto b) { return a + b; }, rnd_cmplx, rnd_cmplx)
      .template run<eve::wide<type>>("KYOSU W-ADD", kyosu::add, rnd_kyosu, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark runner;
    runner.template run<type>("KYOSU S-ARG", kyosu::arg, rnd_kyosu)
      .template run<std::complex<T>>(
        "STD   S-ARG", [](auto a) { return std::arg(a); }, rnd_cmplx)
      .template run<eve::wide<type>>("KYOSU W-ARG", kyosu::arg, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark runner;
    runner.template run<type>("KYOSU S-ASIN", kyosu::asin, rnd_kyosu)
      .template run<std::complex<T>>(
        "STD   S-ASIN", [](auto a) { return std::asin(a); }, rnd_cmplx)
      .template run<eve::wide<type>>("KYOSU W-ASIN", kyosu::asin, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark runner;
    runner.template run<type>("KYOSU S-ATAN", kyosu::atan, rnd_kyosu)
      .template run<std::complex<T>>(
        "STD   S-ATAN", [](auto a) { return std::atan(a); }, rnd_cmplx)
      .template run<eve::wide<type>>("KYOSU W-ATAN", kyosu::atan, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark runner;
    runner.template run<type>("KYOSU S-ATANH", kyosu::atanh, rnd_kyosu)
      .template run<std::complex<T>>(
        "STD   S-ATANH", [](auto a) { return std::atanh(a); }, rnd_cmplx)
      .template run<eve::wide<type>>("KYOSU W-ATANH", kyosu::atanh, rnd_kyosu);
  }
  {
    kyosu::bench::benchmark runner;
    runner.template run<type>("KYOSU S-AVERAGE", kyosu::average, rnd_kyosu, rnd_kyosu)
      .template run<std::complex<T>>(
        "STD   S-AVERAGE", [](auto a, auto b) { return (a + b) / T(2); }, rnd_cmplx, rnd_cmplx)
      .template run<eve::wide<type>>("KYOSU W-AVERAGE", kyosu::average, rnd_kyosu, rnd_kyosu);
  }

  TTS_PASS("Benchmarks - SUCCESS");
};
