//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::expint over reals"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(0,5)
                              )
              )
<typename T>(T a0)
{
  auto r  = T(a0);
  auto resk = kyosu::expint(r);
  auto rese =  eve::exp_int(r);
  std::cout << std::setprecision(16) << "r    " << r    << std::endl;
  std::cout << "resk " << resk << std::endl;
  std::cout << "rese " << rese << std::endl;
  std::cout << std::setprecision(15) << "a0 " << a0 << std::endl;
  TTS_RELATIVE_EQUAL(kyosu::real(resk), rese, tts::prec<T>());
};
