//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::rsqrt over real", kyosu::real_types, tts::randoms(-10, 10))
<typename T>(T v)
{
  using ce_t = kyosu::complex_t<T>;
  auto asq = eve::rsqrt(eve::abs(v));
  TTS_RELATIVE_EQUAL(
    kyosu::rsqrt(v),
    kyosu::if_else(eve::is_gez(v), kyosu::complex(asq, T(0)), kyosu::complex(T(0), eve::signnz(v) * asq)),
    tts::prec<T>());
  auto rr = eve::rsqrt(v);
  auto re = kyosu::rsqrt[kyosu::real_only](v);
  TTS_IEEE_EQUAL(re, rr);
  auto cond = eve::is_ltz(v);

  TTS_RELATIVE_EQUAL(kyosu::rsqrt[cond][kyosu::real_only](v), kyosu::if_else(cond, eve::rsqrt(v), v), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::rsqrt[cond](v), kyosu::if_else(cond, kyosu::rsqrt(v), ce_t(v)), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::rsqrt over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T r, T i)
{
  auto c = kyosu::complex(r, i);
  TTS_RELATIVE_EQUAL(kyosu::rec(kyosu::sqr(kyosu::rsqrt(c))), c, tts::prec<T>());
  auto cond = eve::is_ltz(r);
  TTS_RELATIVE_EQUAL(kyosu::rsqrt[cond](c), kyosu::if_else(cond, kyosu::rsqrt(c), c), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::rsqrt over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto q = type(r, i, j, k);
  TTS_RELATIVE_EQUAL(kyosu::rec(kyosu::sqr((kyosu::rsqrt(q)))), q, tts::prec<T>());
  auto cond = eve::is_ltz(r);
  TTS_RELATIVE_EQUAL(kyosu::rsqrt[cond](q), kyosu::if_else(cond, kyosu::rsqrt(q), q), tts::prec<T>());
};
