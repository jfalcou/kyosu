//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <type_traits>
#include <algorithm>
#include <sstream>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#define TTS_MAIN
#include <tts/tts.hpp>
#include <eve/module/core.hpp>

namespace kyosu::bench
{
  class benchmark
  {
  private:
    ankerl::nanobench::Bench bench;
    std::size_t repetitions;

    std::vector<std::ptrdiff_t> run_cardinals;

    void configure_bench()
    {
      bench.output(nullptr);
      bench.performanceCounters(true);
      bench.epochs(repetitions);
    }

    template<typename TestType, typename Func, typename... Gens>
    void execute_single_run(std::string const& name, Func func, kumi::tuple<Gens...> gens)
    {
      constexpr std::ptrdiff_t N = eve::cardinal_v<TestType>;
      run_cardinals.push_back(N);

      // 1. PURE GENERATION
      auto args = kumi::map([](auto const& g) -> TestType { return TestType(g()); }, gens);

      bench.batch(N);

      // 2. THE HOT LOOP
      bench.run(name, [&]() {
        // A. Anchor Inputs
        kumi::for_each(
          [](auto& arg) {
            if constexpr (eve::product_type<std::decay_t<decltype(arg)>>)
            {
              kumi::for_each([](auto& v) { ankerl::nanobench::doNotOptimizeAway(v); }, arg);
            }
            else { ankerl::nanobench::doNotOptimizeAway(arg); }
          },
          args);

        // B. Pure Execution
        auto res = kumi::apply(func, args);

        // C. Anchor Output
        if constexpr (eve::product_type<std::decay_t<decltype(res)>>)
        {
          kumi::for_each([](auto const& v) { ankerl::nanobench::doNotOptimizeAway(v); }, res);
        }
        else { ankerl::nanobench::doNotOptimizeAway(res); }
      });
    }

  public:
    benchmark(std::size_t repetitions = 2000) : repetitions(repetitions) { configure_bench(); }

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

      // 1. Calculate maximum width of the Benchmark Name column
      std::size_t name_width = 4; // minimum width for "Name"
      for (auto const& res : results) { name_width = std::max(name_width, res.config().mBenchmarkName.size()); }

      // 2. Fixed widths for numerical columns
      int const w_n = 4, w_spd = 9, w_eff = 8, w_cyc = 10, w_min = 8, w_max = 8, w_elem = 12, w_ins = 10;

      // 3. Helper to format a single table row cleanly
      auto print_row = [&](auto n_val, auto n, auto spd, auto eff, auto cyc, auto min, auto max, auto elem, auto ins) {
        out_stream << "| " << std::left << std::setw(name_width) << n_val << " | " << std::right << std::setw(w_n) << n
                   << " | " << std::setw(w_spd) << spd << " | " << std::setw(w_eff) << eff << " | " << std::setw(w_cyc)
                   << cyc << " | " << std::setw(w_min) << min << " | " << std::setw(w_max) << max << " | "
                   << std::setw(w_elem) << elem << " | " << std::setw(w_ins) << ins << " |\n";
      };

      // Print Header
      print_row("Name", "N", "Speedup", "Eff.", "cyc/elem", "min", "max", "elem/s", "ins/elem");

      // Print Perfectly Aligned Markdown Separator
      out_stream << "|:" << std::string(name_width, '-') << "-|" << std::string(w_n + 1, '-') << ":|"
                 << std::string(w_spd + 1, '-') << ":|" << std::string(w_eff + 1, '-') << ":|"
                 << std::string(w_cyc + 1, '-') << ":|" << std::string(w_min + 1, '-') << ":|"
                 << std::string(w_max + 1, '-') << ":|" << std::string(w_elem + 1, '-') << ":|"
                 << std::string(w_ins + 1, '-') << ":|\n";

      // Calculate TRUE baseline throughput (elements per second)
      double baseline_time = results.front().median(ankerl::nanobench::Result::Measure::elapsed);
      double baseline_batch = static_cast<double>(results.front().config().mBatch);
      double baseline_elem_per_sec = baseline_batch / baseline_time;

      bool counters_failed = false;

      for (std::size_t i = 0; i < results.size(); ++i)
      {
        auto const& res = results[i];
        double current_time = res.median(ankerl::nanobench::Result::Measure::elapsed);
        double batch_size = static_cast<double>(res.config().mBatch);
        std::ptrdiff_t N = run_cardinals[i];

        // THE FIX: Calculate speedup based on normalized throughput, not raw batch time
        double elem_per_sec = batch_size / current_time;
        double speedup = elem_per_sec / baseline_elem_per_sec;
        double efficiency = speedup / static_cast<double>(N);

        double ins_per_elem = res.median(ankerl::nanobench::Result::Measure::instructions) / batch_size;
        double cyc_per_elem = res.median(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;
        double min_cyc_elem = res.minimum(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;
        double max_cyc_elem = res.maximum(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;

        if (cyc_per_elem == 0.0 && ins_per_elem == 0.0) { counters_failed = true; }

        // Format strings to ensure exact column alignment
        std::ostringstream spd_str, eff_str;
        if (speedup == 1.0) spd_str << "x1.00";
        else spd_str << "x" << std::fixed << std::setprecision(2) << speedup;

        eff_str << std::fixed << std::setprecision(1) << (efficiency * 100.0) << "%";

        // Helper to format doubles to strings with fixed precision
        auto fmt = [](double v, int p) {
          std::ostringstream oss;
          oss << std::fixed << std::setprecision(p) << v;
          return oss.str();
        };

        print_row(res.config().mBenchmarkName, N, spd_str.str(), eff_str.str(), fmt(cyc_per_elem, 2),
                  fmt(min_cyc_elem, 2), fmt(max_cyc_elem, 2), fmt(elem_per_sec, 0), fmt(ins_per_elem, 2));
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
