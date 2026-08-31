//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
// The Mandelbrot set drawn from the same escape-time algorithm written three ways: std::complex, kyosu on scalars, and
// kyosu on eve::wide. The three answer the same picture, so switching between them changes nothing on screen but the
// frame rate. The keys are listed by usage() below, which the program prints on startup.
//======================================================================================================================
#include <kyosu/kyosu.hpp>

#include <raylib.h>

#include <chrono>
#include <complex>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <sstream>
#include <vector>

using real_t = float;
using wide_t = eve::wide<real_t>;
using scalar_t = kyosu::complex_t<real_t>;

constexpr auto lanes = eve::cardinal_v<wide_t>;

constexpr char const* names[] = {"std::complex", "kyosu scalar", "kyosu wide"};

//== What a kernel's own width entitles it to: one lane for the two scalar ones, one per lane for the wide one.
constexpr double expected_speedup(int kernel)
{
  return kernel == 2 ? double(lanes) : 1.0;
}

struct view
{
  double cx = -0.75, cy = 0.0; // centre of the window, in the plane
  double scale = 3.5 / 960;    // plane units per pixel
  int max_iter = 200;
};

//======================================================================================================================
// The three kernels. Each fills one escape count per pixel, in a buffer whose rows are `stride` wide so that the wide
// one can store a full register on the last column of a row.
//======================================================================================================================
void render_std(std::vector<float>& esc, int w, int h, int stride, view const& v)
{
  for (int y = 0; y < h; ++y)
  {
    auto const im = real_t(v.cy + (y - h / 2) * v.scale);

    for (int x = 0; x < w; ++x)
    {
      std::complex<real_t> const c{real_t(v.cx + (x - w / 2) * v.scale), im};
      std::complex<real_t> z{0, 0};

      int n = 0;
      while (n < v.max_iter && std::norm(z) < real_t(4))
      {
        z = z * z + c;
        ++n;
      }

      esc[y * stride + x] = float(n);
    }
  }
}

void render_scalar(std::vector<float>& esc, int w, int h, int stride, view const& v)
{
  for (int y = 0; y < h; ++y)
  {
    auto const im = real_t(v.cy + (y - h / 2) * v.scale);

    for (int x = 0; x < w; ++x)
    {
      auto const c = kyosu::complex(real_t(v.cx + (x - w / 2) * v.scale), im);
      auto z = scalar_t{0, 0};

      int n = 0;
      while (n < v.max_iter && kyosu::sqr_abs(z) < real_t(4))
      {
        z = kyosu::sqr(z) + c;
        ++n;
      }

      esc[y * stride + x] = float(n);
    }
  }
}

void render_wide(std::vector<float>& esc, int w, int h, int stride, view const& v)
{
  wide_t const lane([](auto i, auto) { return real_t(i); });

  for (int y = 0; y < h; ++y)
  {
    wide_t const im{real_t(v.cy + (y - h / 2) * v.scale)};

    for (int x = 0; x < w; x += lanes)
    {
      // One register of abscissae, then the same iteration as above with the count carried per lane.
      auto const re = eve::fma(lane + real_t(x - w / 2), wide_t(real_t(v.scale)), wide_t(real_t(v.cx)));
      auto const c = kyosu::complex(re, im);

      auto z = kyosu::complex(wide_t(0), wide_t(0));
      wide_t n{0};

      for (int i = 0; i < v.max_iter; ++i)
      {
        auto alive = kyosu::sqr_abs(z) < real_t(4);
        if (eve::none(alive)) break;

        z = kyosu::sqr(z) + c;
        n = eve::inc[alive](n);
      }

      eve::store(n, &esc[y * stride + x]);
    }
  }
}

//======================================================================================================================
// Each kernel timed on the view in front of the viewer, averaged over a few runs. The three answer the same picture,
// so what separates them is the arithmetic alone.
//======================================================================================================================
struct timings
{
  double ms[3] = {0, 0, 0};
};

double time_ms(auto&& render, int runs)
{
  auto const t0 = std::chrono::steady_clock::now();
  for (int i = 0; i < runs; ++i) render();
  auto const t1 = std::chrono::steady_clock::now();

  return std::chrono::duration<double, std::milli>(t1 - t0).count() / runs;
}

timings measure(std::vector<float>& esc, int w, int h, int stride, view const& v, int runs)
{
  return {{time_ms([&] { render_std(esc, w, h, stride, v); }, runs),
           time_ms([&] { render_scalar(esc, w, h, stride, v); }, runs),
           time_ms([&] { render_wide(esc, w, h, stride, v); }, runs)}};
}

void usage()
{
  // The instruction set the binary was built for, which is what decides how many lanes there are to fill.
  std::ostringstream api;
  api << eve::current_api;

  std::printf("\nkyosu - mandelbrot on %s, %d lanes of float\n\n", api.str().c_str(), int(lanes));
  std::printf("  drag          pan\n");
  std::printf("  wheel         zoom on the cursor\n");
  std::printf("  1 2 3         std::complex, kyosu scalar, kyosu wide\n");
  std::printf("  X             time the three on the view in front of you\n");
  std::printf("  keypad - +    iteration budget\n");
  std::printf("  R             back to the whole set\n");
  std::printf("  escape        quit\n");
}

//== The same table on the terminal, where it can be read after the fact and pasted somewhere.
void report(timings const& m, view const& v, int w)
{
  std::printf("\n%d lanes, zoom x%.0f, %d iterations\n", int(lanes), 3.5 / (v.scale * w), v.max_iter);

  for (int i = 0; i < 3; ++i)
  {
    auto const speedup = m.ms[0] / m.ms[i];
    std::printf("  %-13s %7.1f ms  x%-5.2f %3.0f%%\n", names[i], m.ms[i], speedup,
                100.0 * speedup / expected_speedup(i));
  }

  std::printf("  the register alone: x%.2f of x%d\n", m.ms[1] / m.ms[2], int(lanes));
}

//======================================================================================================================
Color colorize(float n, int max_iter)
{
  if (n >= float(max_iter)) return Color{0, 0, 0, 255};

  auto const v = n / float(max_iter);
  auto const b = [](float x) { return std::uint8_t(255.f * std::clamp(1.5f - std::abs(x), 0.f, 1.f)); };

  return Color{b(4.f * v - 3.f), b(4.f * v - 2.f), b(4.f * v - 1.f), 255};
}

//======================================================================================================================
int main()
{
  int w = 960, h = 640;
  int stride = ((w + lanes - 1) / lanes) * lanes;

  SetTraceLogLevel(LOG_WARNING);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(w, h, "kyosu - mandelbrot");
  SetTargetFPS(0);
  usage();

  std::vector<float> esc(std::size_t(stride) * h);
  std::vector<Color> pixels(std::size_t(w) * h);

  Image img{pixels.data(), w, h, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
  Texture2D tex = LoadTextureFromImage(img);

  int backend = 2;
  view v{};

  bool measuring = false;
  timings measured{};

  while (!WindowShouldClose())
  {
    if (IsWindowResized())
    {
      // The plane keeps its scale, so a larger window shows more of it rather than the same picture magnified.
      w = GetScreenWidth();
      h = GetScreenHeight();
      stride = ((w + lanes - 1) / lanes) * lanes;

      esc.assign(std::size_t(stride) * h, 0.f);
      pixels.assign(std::size_t(w) * h, Color{0, 0, 0, 255});

      UnloadTexture(tex);
      img = Image{pixels.data(), w, h, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
      tex = LoadTextureFromImage(img);
    }

    if (IsKeyPressed(KEY_ONE))
    {
      backend = 0;
      measuring = false;
    }
    if (IsKeyPressed(KEY_TWO))
    {
      backend = 1;
      measuring = false;
    }
    if (IsKeyPressed(KEY_THREE))
    {
      backend = 2;
      measuring = false;
    }
    if (IsKeyPressed(KEY_X))
    {
      measured = measure(esc, w, h, stride, v, 3);
      measuring = true;
      report(measured, v, w);
    }
    if (IsKeyPressed(KEY_R)) v = view{};
    // The keypad, whose keys carry the same sign on every layout - GLFW names the main row by its US position.
    if (IsKeyPressed(KEY_KP_SUBTRACT)) v.max_iter = std::max(50, v.max_iter - 50);
    if (IsKeyPressed(KEY_KP_ADD)) v.max_iter += 50;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
      auto const d = GetMouseDelta();
      v.cx -= d.x * v.scale;
      v.cy -= d.y * v.scale;
    }

    if (auto const wheel = GetMouseWheelMove(); wheel != 0)
    {
      // Zoom about the cursor, so what is under it stays under it.
      auto const m = GetMousePosition();
      auto const px = v.cx + (m.x - w / 2) * v.scale;
      auto const py = v.cy + (m.y - h / 2) * v.scale;

      v.scale *= std::pow(0.85, wheel);
      v.cx = px - (m.x - w / 2) * v.scale;
      v.cy = py - (m.y - h / 2) * v.scale;
    }

    switch (backend)
    {
    case 0:
      render_std(esc, w, h, stride, v);
      break;
    case 1:
      render_scalar(esc, w, h, stride, v);
      break;
    default:
      render_wide(esc, w, h, stride, v);
      break;
    }

    for (int y = 0; y < h; ++y)
      for (int x = 0; x < w; ++x) pixels[y * w + x] = colorize(esc[y * stride + x], v.max_iter);

    UpdateTexture(tex, pixels.data());

    BeginDrawing();
    DrawTexture(tex, 0, 0, WHITE);
    DrawRectangle(0, 0, 360, 84, Color{0, 0, 0, 160});
    DrawFPS(12, 12);
    DrawText(TextFormat("%s, %d lane%s", names[backend], backend == 2 ? int(lanes) : 1, backend == 2 ? "s" : ""), 12,
             38, 18, RAYWHITE);
    DrawText(TextFormat("zoom x%.0f, %d iterations", 3.5 / (v.scale * w), v.max_iter), 12, 60, 18, RAYWHITE);

    if (measuring)
    {
      // The default font is not monospaced, so a padded format string cannot line the columns up. Each one is placed
      // by hand instead, the numbers ending where their column does.
      auto right = [](char const* text, int x, int y, Color c) { DrawText(text, x - MeasureText(text, 18), y, 18, c); };

      DrawRectangle(0, 92, 360, 100, Color{0, 0, 0, 160});
      for (int i = 0; i < 3; ++i)
      {
        auto const speedup = measured.ms[0] / measured.ms[i];
        auto const y = 100 + 22 * i;
        auto const c = i == 2 ? YELLOW : RAYWHITE;

        DrawText(names[i], 12, y, 18, c);
        right(TextFormat("%.1f ms", measured.ms[i]), 225, y, c);
        right(TextFormat("x%.2f", speedup), 290, y, c);
        right(TextFormat("%.0f%%", 100.0 * speedup / expected_speedup(i)), 348, y, c);
      }

      // The register on its own: the two kyosu kernels are the same code one type apart, so nothing else separates them.
      DrawText(TextFormat("the register alone: x%.2f of x%d", measured.ms[1] / measured.ms[2], int(lanes)), 12, 166, 18,
               RAYWHITE);
    }

    EndDrawing();
  }

  UnloadTexture(tex);
  CloseWindow();
}
