//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::average over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             )
              )
  <typename T>(T r0, T r1)
{
  TTS_EQUAL(kyosu::harmmean(r0), r0);
  TTS_EQUAL(kyosu::harmmean(r0, r1), eve::harmmean(r0, r1));
  TTS_EQUAL(kyosu::harmmean(r0, r1, r1), eve::harmmean(r0, r1, r1));
  auto cond = eve::is_ltz(r0);
  TTS_EQUAL(kyosu::harmmean[cond](r0, r1, r1), eve::harmmean[cond](r0, r1, r1));
};

TTS_CASE_WITH ( "Check kyosu::harmmean over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             )
              )
<typename T>(T r0, T i0, T r1, T i1)
{
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  TTS_EQUAL(kyosu::harmmean(c0), c0);
  using kyosu::rec;
  auto pr = tts::prec<T>(1.0e-1, 1.0e-6);
  TTS_RELATIVE_EQUAL(kyosu::harmmean(c0, c1), 2*c0*c1/(c0+c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::harmmean(c0, c1, r1), 3*rec(rec(c0)+rec(c1)+rec(r1)), pr);
  TTS_RELATIVE_EQUAL(kyosu::harmmean(r0, c1, r1), 3*rec(rec(r0)+rec(c1)+rec(r1)), pr);

  auto cond = eve::is_ltz(r0);
  TTS_EQUAL(kyosu::harmmean[cond](c0, c1), kyosu::if_else(cond, kyosu::harmmean(c0, c1), c0));
};

TTS_CASE_WITH ( "Check kyosu::harmmean over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1)
{
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0,i0,j0,k0);
  auto q1 = type(r1,i1,j1,k1);
  using kyosu::rec;
  auto pr = tts::prec<T>(1.0e-1, 1.0e-6);
  if constexpr(sizeof(eve::element_type_t<T>) == 8)
  {
    TTS_EQUAL(kyosu::harmmean(q0), q0);
    TTS_RELATIVE_EQUAL(kyosu::harmmean(q0, q1, r1), 3*rec(rec(q0)+rec(q1)+rec(r1)), pr);
    TTS_RELATIVE_EQUAL(kyosu::harmmean(r0, q1, r1), 3*rec(rec(r0)+rec(q1)+rec(r1)), pr);
  }
  auto cond = eve::is_ltz(r0);
  TTS_EQUAL(kyosu::harmmean[cond](q0, q1), kyosu::if_else(cond, kyosu::harmmean(q0, q1), q0));

};
