//! [mandelbrot-all]
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
#include <kyosu/kyosu.hpp>

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <span>

struct RGB { std::uint8_t r, g, b; };

RGB colorize(int iter, int max_iter)
{
  if (iter == max_iter) return {0, 0, 0};

  auto v = static_cast<float>(iter) / static_cast<float>(max_iter);
  auto r = std::clamp(1.5f - std::abs(4.f * v - 3.f), 0.f, 1.f);
  auto g = std::clamp(1.5f - std::abs(4.f * v - 2.f), 0.f, 1.f);
  auto b = std::clamp(1.5f - std::abs(4.f * v - 1.f), 0.f, 1.f);

  return  { static_cast<std::uint8_t>(r * 255.f)
      , static_cast<std::uint8_t>(g * 255.f)
      , static_cast<std::uint8_t>(b * 255.f)
      };
}

void write_ppm(std::span<const int> iterations, int size, int max_iterations, const std::string& filename)
{
  std::ofstream ofs(filename, std::ios::binary);

  // PPM 6 Header
  std::string header = "P6\n" + std::to_string(size) + " " + std::to_string(size) + "\n255\n";
  ofs.write(header.c_str(), header.size());

  std::vector<RGB> pixel_data(iterations.size());
  std::transform( iterations.begin(), iterations.end()
                , pixel_data.begin()
                , [max_iterations](int iter) { return colorize(iter, max_iterations); }
                );

  ofs.write(reinterpret_cast<const char*>(pixel_data.data()), pixel_data.size() * sizeof(RGB));
}


typedef float T;
using wide_t = eve::wide<T>;
using wide_i = eve::wide<int>;
using wide_l = eve::as_logical_t<wide_t>;
using cwide_t= eve::wide<kyosu::complex_t<T>>;

struct mandelbrot
{
  static constexpr auto algt = eve::alignment_v<T>;
  int size, max_iter;
  T x_min, x_max, y_min, y_max, x_range, y_range;
  /*eve::detail::alignas(algt)*/ std::vector<int> iterations;

  mandelbrot(int size_, int max_iter_)
    : size(size_)
    , max_iter(max_iter_)
  {
    x_min   = -2.5;
    x_max   = 1;
    y_min   = -1;
    y_max   = 1;
    x_range = x_max - x_min;
    y_range = y_max - y_min;
    iterations.resize(size * size);
  }

  //! [mandelbrot-scalar]
  void evaluate_scalar()
  {
    for (int i = 0; i < size; ++i) {
      T x0 = T(i) / T(size) * x_range + x_min;
      for (int j = 0; j < size; ++j) {
        int iteration = 0;
        T y0          = T(j) / T(size) * y_range + y_min;
        T x           = 0;
        T y           = 0;
        T x2          = x * x;
        T y2          = y * y;
        while (x2 + y2 < 4 && iteration < max_iter) {
          x2 = x * x;
          y2 = y * y;
          T x_temp = x2 - y2 + x0;
          y        = 2 * x * y + y0;
          x        = x_temp;
          ++iteration;
        }
        iterations[j + i * size] = iteration;
      }
    }
  }
  //! [mandelbrot-scalar]

  //! [mandelbrot-complex-std]
  void evaluate_complex_std()
  {
    using c_t =  std::complex<T>;
    for (int i = 0; i < size; ++i) {
      T  x0(T(i) / T(size) * x_range + x_min);
      for (int j = 0; j < size; ++j) {
        int iteration = 0;
        c_t z0(T(j) / T(size) * y_range + y_min, x0);
        c_t z(0);
        T n2 =  std::norm(z);
        while (n2 < 4 && iteration < max_iter) {
          n2 = std::norm(z);
          z =  z*z + z0;
          ++iteration;
        }
        iterations[j + i * size] = iteration;
      }
    }
  }
  //! [mandelbrot-complex-std]

  //! [mandelbrot-complex-scalar]
  void evaluate_complex_scalar()
  {
    using c_t =  kyosu::complex_t<T>;
    for (int i = 0; i < size; ++i) {
      c_t z0(T(i) / T(size) * x_range + x_min);
      for (int j = 0; j < size; ++j) {
        int iteration = 0;
        kyosu::imag(z0) = T(j) / T(size) * y_range + y_min;
        c_t z(0);
        T n2 =  kyosu::sqr_abs(z);
        while (n2 < 4 && iteration < max_iter) {
          n2 = kyosu::sqr_abs(z);
          z =  kyosu::sqr(z) + z0;
          ++iteration;
        }
        iterations[j + i * size] = iteration;
      }
    }
  }
  //! [mandelbrot-complex-scalar]

//! [mandelbrot-simd]
  void evaluate_simd()
  {
    wide_t step([](auto n, auto){return n; });
    for (int i = 0; i < size; ++i) {
      wide_t x0{T(i) / T(size) * x_range + x_min};
      wide_t fac{y_range / T(size)};
      wide_t y_min_t{y_min};
      for (int j = 0; j < size; j += eve::cardinal_v<wide_t>) {
        int iteration = 0;

        wide_t y0 = eve::fma(step + j, fac, y_min_t);
        wide_t x{0};
        wide_t y{0};
        wide_i iter{0};
        wide_l mask;
        do {
          wide_t x2 = eve::sqr(x);
          wide_t y2 = eve::sqr(y);

          y    = eve::fma(x + x, y, y0);
          x    = x2 - y2 + x0;
          mask = x2 + y2 < 4;
          ++iteration;
          iter = eve::inc[mask](iter);
        } while (eve::any(mask) && iteration < max_iter);
        eve::store(iter, &iterations[j + i * size]);
      }
    }
  }
  //! [mandelbrot-simd]

  //! [mandelbrot-complex-simd]
  void evaluate_complex_simd()
  {
    wide_t step([](auto n, auto){return n; }); // produce a vector containing {0, 1, ..., wide_t::static_size-1}
    for (int i = 0; i < size; ++i) {
      cwide_t z0{T(i) / T(size) * x_range + x_min};
      wide_t fac{y_range / T(size)};
      wide_t y_min_t{y_min};
      for (int j = 0; j < size; j += eve::cardinal_v<wide_t>) {
        int iteration = 0;
        kyosu::imag(z0) = eve::fma(step + j, fac, y_min_t);

        cwide_t z{0};
        wide_i iter{0};
        wide_l mask;
        do {
          wide_t n2 = kyosu::sqr_abs(z);
          z = kyosu::sqr(z) + z0;
          mask = n2 < 4;
          ++iteration;
          iter = eve::inc[mask](iter);
        } while (eve::any(mask) && iteration < max_iter);
        eve::store(iter, &iterations[j + i * size]);
      }
    }
  }
  //! [mandelbrot-complex-simd]

  //! [mandelbrot-complex-simd]-raw
  void evaluate_complex_simd_raw()
  {
    wide_t step([](auto n, auto){return n; }); // produce a vector containing {0, 1, ..., wide_t::static_size-1}
    for (int i = 0; i < size; ++i) {
      cwide_t z0{eve::fma(T(i) / T(size), x_range, x_min)};
      wide_t fac{y_range / T(size)};
      wide_t y_min_t{y_min};
      for (int j = 0; j < size; j += eve::cardinal_v<wide_t>) {
        int iteration = 0;
        kyosu::imag(z0) = eve::fma(step + j, fac, y_min_t);

        cwide_t z{0};
        wide_i iter{0};
        wide_l mask;
        do {
          wide_t n2 = kyosu::sqr_abs(z);
          z = /*eve::raw*/(kyosu::sqr)(z) + z0;
          mask = n2 < T(4);
          ++iteration;
          iter = eve::inc[mask](iter);
        } while (eve::any(mask) && iteration < max_iter);
        eve::store(iter, &iterations[j + i * size]);
      }
    }
  }
  //! [mandelbrot-complex-simd-raw]

};

int main(/*int argc, char** argv*/)
{
  namespace chr = std::chrono;
  using hrc     = chr::high_resolution_clock;

  int size          = 1024;
  int max_iteration = 1000;
  mandelbrot image(size, max_iteration);
  auto t0 = hrc::now();
  image.evaluate_scalar();
  auto t1 = hrc::now();
  std::cout << " scalar " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;

  t0 = hrc::now();
  image.evaluate_complex_std();
  t1 = hrc::now();
  std::cout << " complex std " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;

  t0 = hrc::now();
  image.evaluate_complex_scalar();
  t1 = hrc::now();
  std::cout << " complex scalar " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;

  t0 = hrc::now();
  image.evaluate_simd();
  t1 = hrc::now();
  std::cout << " simd " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;

  auto t0 = hrc::now();
  image.evaluate_complex_simd();
  auto t1 = hrc::now();
  std::cout << " complex simd " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;

  t0 = hrc::now();
  image.evaluate_complex_simd_raw();
  t1 = hrc::now();
  std::cout << " complex simd raw " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;
  // if you want to see the julia set look at the generated julia.ppm by decommenting the line that follows
  //write_ppm(image.iterations, size, max_iteration, "julia.ppm");

}
//! [mandelbrot-all]

// This code can be compiled using
// g++ mandelbrot.cpp -mavx2 -mfma -std=c++20 -O3 -DNDEBUG -o mandelbrot -I/home/jt/falcoudev/kyosu/include


//clang++-21 /home/jt/falcoudev/kyosu/test/doc/mandelbrot.cpp -mavx2 -mfma -std=c++20 -O3 -DNDEBUG -o mandelbrot -I/home/jt/falcoudev/eve/include -I/home/jt/falcoudev/kyosu/include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -I /usr/include/opencv4/
