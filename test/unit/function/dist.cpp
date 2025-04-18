//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::dist over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10)
                             ,tts::randoms(-10,10)
                             )
              )
(auto r0, auto r1)
{
  using e_t =  eve::element_type_t<decltype(r0)>;
  e_t o(1);
  TTS_EQUAL(eve::dist(r0, o),  eve::dist(r0, o));
  TTS_EQUAL(kyosu::dist(r0, r1), eve::dist(r0, r1));
  TTS_EQUAL(kyosu::dist(kyosu::complex(r0), r1), kyosu::dist(kyosu::complex(r0), kyosu::complex(r1)));
  TTS_IEEE_EQUAL(kyosu::dist(kyosu::valmax(eve::as<e_t>()), kyosu::valmin(eve::as<e_t>())), eve::inf(eve::as<e_t>()));
  TTS_IEEE_EQUAL(kyosu::dist(kyosu::nan(eve::as<e_t>()), kyosu::valmin(eve::as<e_t>())), eve::nan(eve::as<e_t>()));
  TTS_IEEE_EQUAL(kyosu::dist(kyosu::inf(eve::as<e_t>()), kyosu::inf(eve::as<e_t>())), eve::nan(eve::as<e_t>()));
  TTS_IEEE_EQUAL(kyosu::dist[eve::pedantic](kyosu::nan(eve::as<e_t>()), kyosu::inf(eve::as<e_t>())), eve::inf(eve::as<e_t>()));
  TTS_IEEE_EQUAL(kyosu::dist[eve::pedantic](kyosu::inf(eve::as<e_t>()), kyosu::inf(eve::as<e_t>())), eve::inf(eve::as<e_t>()));
  TTS_IEEE_EQUAL(kyosu::dist[eve::numeric](kyosu::nan(eve::as<e_t>()), kyosu::nan(eve::as<e_t>())), eve::zero(eve::as<e_t>()));
};

TTS_CASE_WITH ( "Check kyosu::dist over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             ,tts::randoms(-10,10), tts::randoms(-10,10)
                             )
              )
(auto r0, auto i0, auto r1, auto i1)
{
  auto c0 = kyosu::complex(r0,i0);
  auto c1 = kyosu::complex(r1,i1);
  TTS_RELATIVE_EQUAL(kyosu::dist(c0, r1), kyosu::abs(c0-r1), 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::dist(r0, c1), kyosu::abs(r0-c1), 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::dist(c0, c1), kyosu::abs(c0-c1), 1e-7);
  using e_t = decltype(r0);
  using c_t = decltype(c0);
  TTS_IEEE_EQUAL(kyosu::dist(c_t(kyosu::valmax(eve::as<e_t>())), c_t(kyosu::valmin(eve::as<e_t>()))), eve::inf(eve::as<e_t>()));
};

TTS_CASE_WITH ( "Check kyosu::dist over quaternion"
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
  TTS_RELATIVE_EQUAL(kyosu::dist(q0, q1), kyosu::abs(q0-q1) , 1e-7);
};
