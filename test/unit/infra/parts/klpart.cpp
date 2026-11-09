//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::klpart over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::klpart(data), eve::zero(eve::as(data)));
};

TTS_CASE_WITH("Check kyosu::klpart over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  auto z = kyosu::complex(r, i);
  TTS_EQUAL(kyosu::klpart(z), eve::zero(eve::as(r)));
};

TTS_CASE_WITH("Check kyosu::klpart over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
(auto r, auto i, auto j, auto k)
{
  auto q = kyosu::quaternion(r, i, j, k);
  TTS_EQUAL(kyosu::klpart(q), eve::zero(eve::as(r)));
};

TTS_CASE_WITH("Check kyosu::klpart over octonion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
<typename T>(T r, T i, T j, T k, T l, T il, T jl, T kl)
{
  auto o = kyosu::octonion_t<T>(r, i, j, k, l, il, jl, kl);

  TTS_EQUAL(kyosu::klpart(o), kl);

  kyosu::klpart(o) = r;
  TTS_EQUAL(kyosu::klpart(o), r);
};

TTS_CASE("Check that kyosu::klpart reads the product kl")
{
  using o_t = kyosu::octonion_t<double>;
  o_t b{}, l{};
  kyosu::get<3>(b) = 1.;
  kyosu::get<4>(l) = 1.;

  TTS_EQUAL(kyosu::klpart(b * l), 1.);
  TTS_EQUAL(kyosu::klpart(l * b), -1.);
};
