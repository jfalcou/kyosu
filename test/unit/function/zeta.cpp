//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::xi over real", kyosu::real_types, tts::randoms(-10, 10))
<typename T>(T data)
{
  T pi = eve::pi(eve::as(data));
  auto pr = tts::prec<T>();
  TTS_RELATIVE_EQUAL(kyosu::zeta(T(0)), kyosu::complex(T(-0.5)), pr);
  TTS_RELATIVE_EQUAL(kyosu::zeta(T(1)), kyosu::cinf(kyosu::as(kyosu::complex(pi))), pr);
  TTS_RELATIVE_EQUAL(kyosu::zeta(T(2)), kyosu::complex(pi * pi / 6), pr);
  TTS_RELATIVE_EQUAL(kyosu::zeta(T(3)), kyosu::complex(T(1.2020569031595942854)), pr);
  TTS_RELATIVE_EQUAL(kyosu::zeta(T(4)), kyosu::complex(pi * pi * pi * pi / 90), pr);
};

//======================================================================================================================
//== A masked call answers a complex where its argument was real, so the lanes the condition rejects carry complex(v)
//======================================================================================================================
TTS_CASE_WITH("Check kyosu::zeta over a masked real", kyosu::real_types, tts::randoms(-10, 10))
<typename T>(T v)
{
  auto cond = eve::is_ltz(v);

  TTS_RELATIVE_EQUAL(kyosu::zeta[cond](v), kyosu::if_else(cond, kyosu::zeta(v), kyosu::complex_t<T>(v)),
                     tts::prec<T>());
};
