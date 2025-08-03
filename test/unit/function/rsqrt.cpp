//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::rsqrt over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>  (T v)
{
  auto asq = eve::rsqrt(eve::abs(v));
  TTS_RELATIVE_EQUAL(kyosu::rsqrt(v),  kyosu::if_else(eve::is_gez(v)
                                                    , kyosu::complex(asq, T(0))
                                                     , kyosu::complex(T(0), eve::signnz(v)*asq)), tts::prec<T>());
  auto rr = eve::rsqrt(v);
  auto re = kyosu::rsqrt[kyosu::real_only](v);
  TTS_IEEE_EQUAL(re, kyosu::inject(rr));
};

TTS_CASE_WITH ( "Check kyosu::rsqrt over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
(auto r, auto i)
{
  using T =  decltype(r);
  auto c = kyosu::complex(r,i);
  TTS_RELATIVE_EQUAL(kyosu::rec(kyosu::sqr(kyosu::rsqrt(c))), c, tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::rsqrt over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto q = type(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::rec(kyosu::sqr((kyosu::rsqrt(q)))), q, tts::prec<T>());
};
