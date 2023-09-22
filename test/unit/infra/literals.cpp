//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE( "Check literals behavior")
{
  using namespace kyosu;

  TTS_EQUAL( 3.25_i , (kyosu::complex    (0. ,3.25           )));
  TTS_EQUAL( 3.25_if, (kyosu::complex    (0.f,3.25f          )));
  TTS_EQUAL( 3.25_j , (kyosu::quaternion (0. ,0. ,3.25 ,0.   )));
  TTS_EQUAL( 3.25_jf, (kyosu::quaternion (0.f,0.f,3.25f,0.f  )));
  TTS_EQUAL( 3.25_k , (kyosu::quaternion (0. ,0. ,0.   ,3.25 )));
  TTS_EQUAL( 3.25_kf, (kyosu::quaternion (0.f,0.f,0.f  ,3.25f)));
};

TTS_CASE( "Check literals composition")
{
  using namespace kyosu;

  TTS_EQUAL( 1. - 2._i               , (kyosu::complex    (1.,-2.     )));
  TTS_EQUAL( 1. - 2._i + 3._j        , (kyosu::quaternion (1.,-2.,3.,0. )));
  TTS_EQUAL( 1. - 2._i + 3._j - 4._k , (kyosu::quaternion (1.,-2.,3.,-4.)));

  TTS_EQUAL( 1. - 2._if                 , (kyosu::complex    (1.f,-2.f     )));
  TTS_EQUAL( 1. - 2._if + 3._jf         , (kyosu::quaternion (1.f,-2.f,3.f,0.f )));
  TTS_EQUAL( 1. - 2._if + 3._jf - 4._kf , (kyosu::quaternion (1.f,-2.f,3.f,-4.f)));
};
