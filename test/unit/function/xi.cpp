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
  TTS_RELATIVE_EQUAL(kyosu::xi(T(0)), kyosu::complex(T(0.5)), pr);
  TTS_RELATIVE_EQUAL(kyosu::xi(T(1)), kyosu::complex(T(0.5)), pr);
  TTS_RELATIVE_EQUAL(kyosu::xi(T(2)), kyosu::complex(pi / 6), pr);
  TTS_RELATIVE_EQUAL(kyosu::xi(T(4)), kyosu::complex(pi * pi / 15), pr);
  TTS_RELATIVE_EQUAL(kyosu::xi(T(0.5)), kyosu::complex(T(0.497120778188314109912)), pr);
  TTS_RELATIVE_EQUAL(kyosu::xi(T(-0.5)), kyosu::complex(T(0.50873103872632395802)), pr);
  TTS_IEEE_EQUAL(kyosu::xi(kyosu::nan(kyosu::as(kyosu::complex(pi)))), kyosu::fnan(kyosu::as(kyosu::complex(pi))));
  TTS_IEEE_EQUAL(kyosu::xi(kyosu::cinf(kyosu::as(kyosu::complex(pi)))), kyosu::fnan(kyosu::as(kyosu::complex(pi))));
};
