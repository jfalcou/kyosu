//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check behavior of arg on reals"
              , kyosu::real_types
              , tts::generate( tts::randoms(1, 10), tts::randoms(-10,-1) )
              )
(auto p, auto n)
{
  TTS_EQUAL(kyosu::arg(p), eve::zero(eve::as(p)));
  TTS_EQUAL(kyosu::arg(n), eve::pi(eve::as(n))  );
};

TTS_CASE_WITH ( "Check behavior of arg on complex"
              , kyosu::real_types
              , tts::generate( tts::randoms(-10, 10), tts::randoms(-10,10) )
              )
(auto r, auto i)
{
  using namespace kyosu;
  auto z  = kyosu::complex(r,i);
  auto ref_args = eve::atan2[eve::pedantic]( eve::sign(imag(z)) * kyosu::abs(pure(z)), real(z));
  TTS_EQUAL(kyosu::arg(z), ref_args);
};

TTS_CASE_WITH ( "Check behavior of arg on quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10, 10), tts::randoms(-10,10)
                              , tts::randoms(-10, 10), tts::randoms(-10,10)
                              )
              )
(auto r, auto i, auto j, auto k)
{
  using namespace kyosu;
  auto z  = kyosu::quaternion(r,i,j,k);
  auto ref_args = eve::atan2[eve::pedantic]( eve::sign(imag(z)) * kyosu::abs(pure(z)), real(z));
  TTS_EQUAL(kyosu::arg(z), ref_args);
};
