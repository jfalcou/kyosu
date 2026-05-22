//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <type_traits>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#define TTS_MAIN
#include <tts/tts.hpp>
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <eve/memory/align.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/module/algo/algo/container/soa_vector.hpp>

namespace kyosu::bench
{
  template<typename T> struct data_storage
  {
    using type = std::vector<eve::element_type_t<T>, eve::aligned_allocator<T>>;
  };

  template<eve::product_type T> struct data_storage<T>
  {
    using type = eve::algo::soa_vector<eve::element_type_t<T>>;
  };

  class benchmark
  {
  private:
    ankerl::nanobench::Bench bench;
    std::size_t dataSize;
    std::size_t repetitions;

    std::vector<std::ptrdiff_t> run_cardinals;

    void configure_bench()
    {
      bench.output(nullptr);
      bench.performanceCounters(true);
      bench.epochs(repetitions);
      bench.batch(dataSize);
    }

    template<typename C> static void fill_with(C& data, auto fn)
    {
      if constexpr (eve::product_type<typename C::value_type>)
      {
        for (std::size_t i = 0; i < data.size(); i++) data.set(i, fn());
      }
      else { std::generate(data.begin(), data.end(), fn); }
    }

    template<typename C> static auto get_value(C const& data, int i)
    {
      if constexpr (eve::product_type<typename C::value_type>) return data.get(i);
      else return data[i];
    }

    template<typename TestType, typename Func, typename... Gens>
    void execute_single_run(std::string const& name, Func func, kumi::tuple<Gens...> gens)
    {
      constexpr std::ptrdiff_t N = eve::cardinal_v<TestType>;
      run_cardinals.push_back(N);

      std::size_t alignedDataSize = eve::align(dataSize, eve::over{static_cast<std::size_t>(N)});

      // 1. Allocate Input Data
      kumi::tuple<typename data_storage<std::invoke_result_t<Gens>>::type...> data;
      kumi::for_each(
        [&](auto& d, auto const& g) {
          d.resize(alignedDataSize);
          fill_with(d, g);
        },
        data, gens);

      // 2. Allocate Output Buffer
      using ElementType = eve::element_type_t<TestType>;
      typename data_storage<ElementType>::type out;
      out.resize(alignedDataSize);

      bench.batch(alignedDataSize);

      bench.run(name, [&]() {
        if constexpr (std::is_same_v<TestType, ElementType>)
        {
          // SCALAR PATH
          for (std::size_t i = 0; i < alignedDataSize; ++i)
          {
            auto elems = kumi::map([&](auto const& d) { return get_value(d, i); }, data);
            auto res = kumi::apply(func, elems);

            if constexpr (eve::product_type<ElementType>) out.set(i, res);
            else out[i] = res;
          }
        }
        else
        {
          // SIMD PATH: Zip inputs and output together
          kumi::apply(
            [&](auto&... d_in) {
              eve::algo::for_each(eve::views::zip(d_in..., out), [&](auto ds, auto ignore) {
                // Cleanly separate the output iterator from the input iterators using kumi
                auto in_iters = kumi::pop_back(ds);
                auto out_iter = kumi::back(ds);

                // Load, Compute, and Store transparently to preserve EVE's loop unrolling
                auto elems = kumi::map([&](auto it) { return eve::load[ignore](it); }, in_iters);
                auto res = kumi::apply(func, elems);
                eve::store[ignore](res, out_iter);
              });
            },
            data);
        }
      });

      // 3. Global Sink
      if constexpr (eve::product_type<ElementType>) ankerl::nanobench::doNotOptimizeAway(out.get(0));
      else ankerl::nanobench::doNotOptimizeAway(out[0]);
    }

  public:
    benchmark(std::size_t dataSize = 4096, std::size_t repetitions = 2000)
      : dataSize(dataSize), repetitions(repetitions)
    {
      configure_bench();
    }

    ~benchmark() { report(); }

    benchmark& reset()
    {
      bench = ankerl::nanobench::Bench();
      run_cardinals.clear();
      configure_bench();
      return *this;
    }

    template<typename TestType, typename Func, typename... Generators>
    benchmark& run(std::string const& name, Func func, Generators const&... g)
    {
      execute_single_run<TestType>(name, func, kumi::tuple<Generators...>{g...});
      return *this;
    }

    benchmark& report(std::ostream& out_stream = std::cout)
    {
      auto const& results = bench.results();
      if (results.empty()) return *this;

      out_stream << "| Name | N | Speedup | Eff. | cyc/elem | min | max | elem/s | ins/elem |\n";
      out_stream << "|:---|---:|---:|---:|---:|---:|---:|---:|---:|\n";

      double baseline_time = results.front().median(ankerl::nanobench::Result::Measure::elapsed);
      bool counters_failed = false;

      for (std::size_t i = 0; i < results.size(); ++i)
      {
        auto const& res = results[i];
        double current_time = res.median(ankerl::nanobench::Result::Measure::elapsed);
        double batch_size = static_cast<double>(res.config().mBatch);
        std::ptrdiff_t N = run_cardinals[i];

        double speedup = baseline_time / current_time;
        double efficiency = speedup / static_cast<double>(N);
        double elem_per_sec = batch_size / current_time;

        double ins_per_elem = res.median(ankerl::nanobench::Result::Measure::instructions) / batch_size;
        double cyc_per_elem = res.median(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;
        double min_cyc_elem = res.minimum(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;
        double max_cyc_elem = res.maximum(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;

        if (cyc_per_elem == 0.0 && ins_per_elem == 0.0) { counters_failed = true; }

        out_stream << "| " << res.config().mBenchmarkName << " | " << N << " | ";

        if (speedup == 1.0) out_stream << "x1.00 | ";
        else out_stream << "x" << std::fixed << std::setprecision(2) << speedup << " | ";

        out_stream << std::fixed << std::setprecision(1) << (efficiency * 100.0) << "% | " << std::fixed
                   << std::setprecision(2) << cyc_per_elem << " | " << std::setprecision(2) << min_cyc_elem << " | "
                   << std::setprecision(2) << max_cyc_elem << " | " << std::setprecision(0) << elem_per_sec << " | "
                   << std::setprecision(2) << ins_per_elem << " |\n";
      }

      if (counters_failed)
      {
        out_stream << "\n> Note: CPU cycles and instructions were 0.00. OS blocked hardware counters.\n";
      }

      out_stream << "\n" << std::flush;
      return *this;
    }
  };
}
