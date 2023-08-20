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

  TTS_EQUAL( 3.25_i , (kyosu::complex<double>    {0. ,3.25           }));
  TTS_EQUAL( 3.25_if, (kyosu::complex<float>     {0.f,3.25f          }));
  TTS_EQUAL( 3.25_j , (kyosu::quaternion<double> {0. ,0. ,3.25 ,0.   }));
  TTS_EQUAL( 3.25_jf, (kyosu::quaternion<float>  {0.f,0.f,3.25f,0.f  }));
  TTS_EQUAL( 3.25_k , (kyosu::quaternion<double> {0. ,0. ,0.   ,3.25 }));
  TTS_EQUAL( 3.25_kf, (kyosu::quaternion<float>  {0.f,0.f,0.f  ,3.25f}));
};

TTS_CASE( "Check literals composition")
{
  using namespace kyosu;

  TTS_EQUAL( 1. - 2._i               , (kyosu::complex<double>    {1,-2     }));
  TTS_EQUAL( 1. - 2._i + 3._j        , (kyosu::quaternion<double> {1,-2,3,0 }));
  TTS_EQUAL( 1. - 2._i + 3._j - 4._k , (kyosu::quaternion<double> {1,-2,3,-4}));

  TTS_EQUAL( 1. - 2._if                 , (kyosu::complex<float>    {1,-2     }));
  TTS_EQUAL( 1. - 2._if + 3._jf         , (kyosu::quaternion<float> {1,-2,3,0 }));
  TTS_EQUAL( 1. - 2._if + 3._jf - 4._kf , (kyosu::quaternion<float> {1,-2,3,-4}));
};
