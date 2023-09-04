//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::powm1 over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10)
                             ,tts::between(-10,10)
                             )
              )
(auto r0, auto r1)
{
  TTS_EQUAL(kyosu::powm1(r0, r1), eve::powm1(r0, r1));
//  TTS_RELATIVE_EQUAL(kyosu::powm1(r0, 4),  kyosu::sqr(kyosu::sqr(r0)), 1.0e-5);
};

TTS_CASE_WITH ( "Check kyosu::powm1 over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10)
                             ,tts::between(-10,10), tts::between(-10,10)
                             )
              )
(auto r0, auto i0, auto r1, auto i1)
{
  auto c0 = kyosu::to_complex(r0,i0);
  auto c1 = kyosu::to_complex(r1,i1);
  TTS_RELATIVE_EQUAL(kyosu::powm1(c0, c1), kyosu::dec(kyosu::exp(c1*kyosu::log(c0))), 1e-5);
  TTS_RELATIVE_EQUAL(kyosu::powm1(r0, c1), kyosu::dec(kyosu::exp(c1*kyosu::log(r0))), 1e-5);
  TTS_RELATIVE_EQUAL(kyosu::powm1(c0, r1), kyosu::dec(kyosu::exp(r1*kyosu::log(c0))), 1e-5);
//  TTS_RELATIVE_EQUAL(kyosu::powm1(c0, 4u),  kyosu::dec(c0*kyosu::sqr(kyosu::sqr(c0))), 1.0e-5);

   auto o = 1.0f;
   auto oo = kyosu::to_complex(o+o, o);
   auto z =  kyosu::if_else(4 <  2, o*oo, o);
   std::cout << "o  " << o << std::endl;
   std::cout << "oo " << oo << std::endl;
   std::cout << "o*oo " << o*oo << std::endl;
   std::cout << "z  " << z << std::endl;
};

TTS_CASE_WITH ( "Check kyosu::powm1 over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1)
{
  using type = kyosu::as_quaternion_t<T>;
  auto q0 = type(r0,i0,j0,k0);
  auto q1 = type(r1,i1,j1,k1);
  TTS_RELATIVE_EQUAL(kyosu::powm1(q0, q1),  kyosu::dec(kyosu::exp(q1*kyosu::log((q0)))), 1e-5);
//  TTS_RELATIVE_EQUAL(kyosu::powm1(q0, 4),  kyosu::dec(kyosu::sqr(kyosu::sqr(q0))), 1.0e-5);
};
