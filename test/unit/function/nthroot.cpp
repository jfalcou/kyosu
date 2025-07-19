//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::nthroot over real"
              , kyosu::simd_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r0)
{
  using wi_t =  eve::wide<unsigned int, eve::fixed<T::size()>>;
  T fn(eve::floor(eve::iota(eve::as<T>())/2)+1);
  wi_t n(eve::iota(eve::as<wi_t>())/2+1);
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(r0, n), fn), kyosu::complex(r0), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(r0, fn), fn), kyosu::complex(r0), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::real(kyosu::nthroot[kyosu::real_only](r0, fn)), eve::nthroot(r0, fn), tts::prec<T>() );
};

TTS_CASE_WITH ( "Check kyosu::nthroot over complex"
              , kyosu::simd_real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             )
              )
  (auto r0, auto i0)
{
  using T =  decltype(r0);
  auto c0 = kyosu::complex(r0,i0);
  T fn(eve::iota(eve::as<T>())+1);
  using wi_t =  eve::wide<unsigned int, eve::fixed<T::size()>>;
  wi_t n(eve::iota(eve::as<wi_t>())+1);
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(c0, n), fn), c0, tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(c0, fn), fn), c0, tts::prec<T>() );
};
