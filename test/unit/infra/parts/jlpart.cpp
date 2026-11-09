//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::jlpart over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::jlpart(data), eve::zero(eve::as(data)));
};

TTS_CASE_WITH("Check kyosu::jlpart over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  auto z = kyosu::complex(r, i);
  TTS_EQUAL(kyosu::jlpart(z), eve::zero(eve::as(r)));
};

TTS_CASE_WITH("Check kyosu::jlpart over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
(auto r, auto i, auto j, auto k)
{
  auto q = kyosu::quaternion(r, i, j, k);
  TTS_EQUAL(kyosu::jlpart(q), eve::zero(eve::as(r)));
};

TTS_CASE_WITH("Check kyosu::jlpart over octonion",
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

  TTS_EQUAL(kyosu::jlpart(o), jl);

  kyosu::jlpart(o) = r;
  TTS_EQUAL(kyosu::jlpart(o), r);
};

TTS_CASE("Check that kyosu::jlpart reads the product jl")
{
  using o_t = kyosu::octonion_t<double>;
  o_t b{}, l{};
  kyosu::get<2>(b) = 1.;
  kyosu::get<4>(l) = 1.;

  TTS_EQUAL(kyosu::jlpart(b * l), 1.);
  TTS_EQUAL(kyosu::jlpart(l * b), -1.);
};
