//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::conj over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::conj(data), data);
};

TTS_CASE_WITH ( "Check kyosu::conj over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::conj(kyosu::complex(r,i)), kyosu::complex(r,-i));
  TTS_IEEE_EQUAL(kyosu::conj(kyosu::complex(eve::nan(eve::as(r)),i)) , kyosu::complex(eve::nan(eve::as(r)),-i));
  TTS_IEEE_EQUAL(kyosu::conj(kyosu::complex(r,eve::nan(eve::as(i)))) , kyosu::complex(r,eve::nan(eve::as(i))));
};

TTS_CASE_WITH ( "Check kyosu::conj over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::conj(type(r,i,j,k)), type(r,-i,-j,-k));
};
