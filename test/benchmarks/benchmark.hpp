//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <utility>
#include <type_traits>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#define TTS_MAIN
#include <tts/tts.hpp>
#include <eve/module/core.hpp>

#define TTS_RUN_BENCHMARK(RUNNER, TYPE, NAME, FUNC, ...) (RUNNER).run<TYPE>(NAME, FUNC, __VA_ARGS__)
#define TTS_RUN_BENCHMARK_TPL(RUNNER, TYPE, NAME, FUNC, ...) (RUNNER).template run<TYPE>(NAME, FUNC, __VA_ARGS__)

namespace kyosu::bench
{
  class benchmark
  {
  private:
    ankerl::nanobench::Bench bench;
    std::size_t repetitions;

    tts::buffer<std::ptrdiff_t> run_cardinals;
    tts::text base_type_name;
    tts::text base_file_name;

    void configure_bench()
    {
      bench.output(nullptr);
      bench.performanceCounters(true);
      bench.epochs(repetitions);
    }

    template<typename TestType, typename Func, typename... Gens>
    void execute_single_run(tts::text const& name, Func&& func, kumi::tuple<Gens...> const& gens)
    {
      base_type_name = ::tts::as_text(::tts::typename_<TestType>);

      constexpr std::ptrdiff_t N = eve::cardinal_v<TestType>;
      run_cardinals.push_back(N);

      // 1. PURE GENERATION
      auto args = kumi::map([](auto const& g) -> TestType { return TestType(g()); }, gens);

      bench.batch(N);

      // 2. THE HOT LOOP
      bench.run(name.data(), [&]() {
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
        auto res = kumi::apply(std::forward<Func>(func), args);

        // C. Anchor Output
        if constexpr (eve::product_type<std::decay_t<decltype(res)>>)
        {
          kumi::for_each([](auto const& v) { ankerl::nanobench::doNotOptimizeAway(v); }, res);
        }
        else { ankerl::nanobench::doNotOptimizeAway(res); }
      });
    }

  public:
    // Fallback constructor for when no name is provided (or just repetitions are provided)
    benchmark(std::size_t repetitions = 2000) : repetitions(repetitions), base_file_name(tts::text("benchmark"))
    {
      configure_bench();
    }

    // Auto constructor for string literals.
    // The constraint prevents integers from accidentally trapping here instead of the repetitions constructor.
    benchmark(auto const& name, std::size_t repetitions = 2000)
    requires(!std::is_integral_v<std::decay_t<decltype(name)>>)
      : repetitions(repetitions), base_file_name(tts::text(name))
    {
      configure_bench();
    }

    ~benchmark() { report(); }

    benchmark& reset()
    {
      bench = ankerl::nanobench::Bench();
      // tts::buffer lacks .clear(), so we just move-assign a fresh empty instance
      run_cardinals = tts::buffer<std::ptrdiff_t>();
      configure_bench();
      return *this;
    }

    template<typename TestType, typename Name, typename Func, typename... Generators>
    benchmark& run(Name const& name, Func&& func, Generators const&... g)
    {
      execute_single_run<TestType>(tts::text(name), std::forward<Func>(func), kumi::tuple<Generators...>{g...});
      return *this;
    }

    benchmark& report(std::ostream& out_stream = std::cout)
    {
      auto const& results = bench.results();
      if (results.empty()) return *this;

      // ---------------------------------------------------------------------------------------------------------------
      // CLI Argument parsing for raw sample dumping (Transposed Columns)
      if (::tts::arguments()("-d", "--dump"))
      {
        // Construct custom CSV name based on the runner's instantiated name
        tts::text filename = base_file_name + ".csv";
        std::ofstream out_file(filename.data());

        // Extract raw elapsed times using Mustache into a temporary stringstream
        std::stringstream ss;
        bench.render("{{#result}}{{#measurement}}{{elapsed}} {{/measurement}}\n{{/result}}", ss);

        std::string raw_dump = ss.str();
        char const* ptr = raw_dump.c_str();

        // Parse the text block cleanly into a 2D grid
        tts::buffer<tts::buffer<double>> grid;
        for (std::size_t i = 0; i < results.size(); ++i)
        {
          tts::buffer<double> row;

          // Retrieve the lane count (N) to normalize time-per-lambda into time-per-element
          double current_N = static_cast<double>(run_cardinals[i]);

          while (*ptr != '\n' && *ptr != '\0')
          {
            char* end = nullptr;
            double val = std::strtod(ptr, &end);
            if (ptr != end)
            {
              row.push_back(val / current_N); // Normalize here!
              ptr = end;
            }
            else { break; }
            while (*ptr == ' ') ++ptr;
          }
          if (*ptr == '\n') ++ptr;
          grid.push_back(std::move(row));
        }

        // Write Transposed CSV: Headers (1 Column per benchmark run)
        for (std::size_t i = 0; i < results.size(); ++i)
        {
          tts::text header{"%s", results[i].config().mBenchmarkName.c_str()};
          out_file << header.data();
          if (i + 1 < results.size()) out_file << ",";
        }
        out_file << "\n";

        // Find maximum columns (epochs) across all runs
        std::size_t max_epochs = 0;
        for (std::size_t i = 0; i < grid.size(); ++i) { max_epochs = tts::_::max(max_epochs, grid[i].size()); }

        // Write Transposed CSV: Columns (Measurement data pivoting)
        for (std::size_t epoch = 0; epoch < max_epochs; ++epoch)
        {
          for (std::size_t col = 0; col < grid.size(); ++col)
          {
            if (epoch < grid[col].size())
            {
              tts::text val{"%g", grid[col][epoch]};
              out_file << val.data();
            }
            if (col + 1 < grid.size()) out_file << ",";
          }
          out_file << "\n";
        }
      }
      // ---------------------------------------------------------------------------------------------------------------

      // Print Header Section
      out_stream << "# Benchmarking for : `" << base_file_name.data() << "`\n";
      out_stream << "**SIMD Architecture:** `" << eve::current_api << "`\n\n";

      // 1. Calculate maximum width of the Benchmark Name column using TTS max
      std::size_t name_width = 4;
      for (auto const& res : results) { name_width = tts::_::max(name_width, res.config().mBenchmarkName.size()); }

      // 2. Fixed widths for numerical columns
      int const w_n = 4, w_spd = 9, w_eff = 8, w_cyc = 10, w_min = 8, w_max = 8, w_elem = 12, w_ins = 10;

      // 3. printf-style row formatting utility using tts::text dynamic widths (*)
      auto print_row = [&](char const* n_val, char const* n, char const* spd, char const* eff, char const* cyc,
                           char const* min, char const* max, char const* elem, char const* ins) {
        tts::text row{"| %-*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s |\n",
                      static_cast<int>(name_width),
                      n_val,
                      w_n,
                      n,
                      w_spd,
                      spd,
                      w_eff,
                      eff,
                      w_cyc,
                      cyc,
                      w_min,
                      min,
                      w_max,
                      max,
                      w_elem,
                      elem,
                      w_ins,
                      ins};
        out_stream << row.data();
      };

      print_row("Name", "N", "Speedup", "Eff.", "cyc/elem", "min", "max", "elem/s", "ins/elem");

      // Perfectly aligned Markdown separators without stream manipulators
      auto dashes = [&](int count) {
        while (count-- > 0) out_stream << '-';
      };

      out_stream << "|:";
      dashes(static_cast<int>(name_width));
      out_stream << "-|";
      dashes(w_n + 1);
      out_stream << ":|";
      dashes(w_spd + 1);
      out_stream << ":|";
      dashes(w_eff + 1);
      out_stream << ":|";
      dashes(w_cyc + 1);
      out_stream << ":|";
      dashes(w_min + 1);
      out_stream << ":|";
      dashes(w_max + 1);
      out_stream << ":|";
      dashes(w_elem + 1);
      out_stream << ":|";
      dashes(w_ins + 1);
      out_stream << ":|\n";

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

        double elem_per_sec = batch_size / current_time;
        double speedup = elem_per_sec / baseline_elem_per_sec;
        double efficiency = speedup / static_cast<double>(N);

        double ins_per_elem = res.median(ankerl::nanobench::Result::Measure::instructions) / batch_size;
        double cyc_per_elem = res.median(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;
        double min_cyc_elem = res.minimum(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;
        double max_cyc_elem = res.maximum(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;

        if (cyc_per_elem == 0.0 && ins_per_elem == 0.0) { counters_failed = true; }

        // Pre-format everything to const char*
        tts::text n_str{"%td", N};
        tts::text spd_str = (speedup == 1.0) ? tts::text("x1.00") : tts::text("x%.2f", speedup);
        tts::text eff_str{"%.1f%%", efficiency * 100.0};
        tts::text cyc_str{"%.2f", cyc_per_elem};
        tts::text min_str{"%.2f", min_cyc_elem};
        tts::text max_str{"%.2f", max_cyc_elem};
        tts::text elem_str{"%.0f", elem_per_sec};
        tts::text ins_str{"%.2f", ins_per_elem};

        print_row(res.config().mBenchmarkName.c_str(), n_str.data(), spd_str.data(), eff_str.data(), cyc_str.data(),
                  min_str.data(), max_str.data(), elem_str.data(), ins_str.data());
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
