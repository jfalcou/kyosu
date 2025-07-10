//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sqrt over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>  (T v)
{
  using ce_t = kyosu::complex_t<T>;
  auto asq = eve::sqrt(eve::abs(v));
  TTS_RELATIVE_EQUAL(kyosu::sqrt(v),  kyosu::if_else(eve::is_gez(v)
                                                    , kyosu::complex(asq, T(0))
                                                    , kyosu::complex(T(0), asq)), tts::prec<T>());
  auto rr = eve::sqrt(v);
  auto re = kyosu::sqrt[kyosu::real_only](v);
  TTS_IEEE_EQUAL(re,  ce_t(rr, eve::if_else(eve::is_nan(rr), eve::nan(eve::as(rr)), eve::zero)));
};

TTS_CASE_WITH ( "Check kyosu::sqrt over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
(auto r, auto i)
{
  using T =  decltype(r);
  auto c = kyosu::complex(r,i);
  TTS_RELATIVE_EQUAL(kyosu::sqr(kyosu::sqrt(c)), c, tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::sqrt over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto q = type(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::sqr((kyosu::sqrt(q))), q, tts::prec<T>());
};
