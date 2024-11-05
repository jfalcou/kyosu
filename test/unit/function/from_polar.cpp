//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::from_polar over real"
              , kyosu::real_types
              , tts::generate( tts::randoms(0,10) ,tts::randoms(-10,10)
                             , tts::randoms(-10,10), tts::randoms(-10,10)
                             , tts::randoms(-10,10), tts::randoms(-10,10)
                             )
              )
(auto rho, auto theta, auto , auto , auto , auto )
{
  // auto iq = kyosu::sign(kyosu::quaternion(r,i,j,k));
  // TTS_RELATIVE_EQUAL(kyosu::from_polar(rho, theta, iq), rho*kyosu::exp(theta*iq), 1.0e-5);
  TTS_RELATIVE_EQUAL(kyosu::from_polar(rho, theta),     rho*kyosu::exp_i(theta),  1.0e-5);
};
