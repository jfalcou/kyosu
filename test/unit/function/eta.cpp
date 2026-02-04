//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::eta over real", kyosu::real_types, tts::randoms(-10, 10))
<typename T>(T data)
{
  T pi = eve::pi(eve::as(data));
  auto pr = tts::prec<T>();
  TTS_RELATIVE_EQUAL(kyosu::eta(T(0)), kyosu::complex(T(0.5)), pr);
  TTS_RELATIVE_EQUAL(kyosu::eta(T(1)), kyosu::complex(eve::log(T(2))), pr);
  TTS_RELATIVE_EQUAL(kyosu::eta(T(2)), kyosu::complex(pi * pi / 12), pr);
  TTS_RELATIVE_EQUAL(kyosu::eta(T(3)), kyosu::complex(T(0.9015426773696957140)), pr);
  TTS_RELATIVE_EQUAL(kyosu::eta(T(4)), kyosu::complex(7 * pi * pi * pi * pi / 720), pr);
};
