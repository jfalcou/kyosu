//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::sqrt over real", kyosu::real_types, tts::randoms(-10, 10))
<typename T>(T v)
{
  using ce_t = kyosu::complex_t<T>;
  auto asq = eve::sqrt(eve::abs(v));
  TTS_RELATIVE_EQUAL(kyosu::sqrt(v),
                     kyosu::if_else(eve::is_gez(v), kyosu::complex(asq, T(0)), kyosu::complex(T(0), asq)),
                     tts::prec<T>());
  auto rr = eve::sqrt(v);
  auto re = kyosu::sqrt[kyosu::real_only](v);
  TTS_IEEE_EQUAL(re, rr);
  auto x = kyosu::sqrt(kyosu::complex(T(-4), T(-0.0)));
  TTS_IEEE_EQUAL(x, kyosu::complex(T(0.0), T(-2.0)));
  auto y = kyosu::sqrt(kyosu::complex(T(-4), T(0.0)));
  TTS_IEEE_EQUAL(y, kyosu::complex(T(0.0), T(2.0)));
  auto cond = eve::is_ltz(v);

  TTS_RELATIVE_EQUAL(kyosu::sqrt[cond][kyosu::real_only](v), kyosu::if_else(cond, eve::sqrt(v), v), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::sqrt[cond](v), kyosu::if_else(cond, kyosu::sqrt(v), ce_t(v)), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::sqrt over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  using T = decltype(r);
  auto c = kyosu::complex(r, i);
  auto sc = kyosu::sqrt(c);
  TTS_RELATIVE_EQUAL(kyosu::sqr(sc), c, tts::prec<T>());
  TTS_EXPECT(eve::all(eve::sign(i) == eve::sign(kyosu::imag(sc))));
  auto cond = eve::is_ltz(r);
  TTS_RELATIVE_EQUAL(kyosu::sqrt[cond](c), kyosu::if_else(cond, kyosu::sqrt(c), c), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::sqrt over quaternion",
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
  TTS_RELATIVE_EQUAL(kyosu::sqr((kyosu::sqrt(q))), q, tts::prec<T>());
  auto cond = eve::is_ltz(r);
  TTS_RELATIVE_EQUAL(kyosu::sqrt[cond](q), kyosu::if_else(cond, kyosu::sqrt(q), q), tts::prec<T>());
};
