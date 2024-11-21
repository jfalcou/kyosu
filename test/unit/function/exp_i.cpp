//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::exp_i over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(0.5,2.0), tts::randoms(0.5,2.0)
                              , tts::randoms(0.5,2.0), tts::randoms(0.5,2.0)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using u_t = eve::underlying_type_t<T>;
  constexpr auto ii = kyosu::complex_t<u_t>(u_t(0), u_t(1));

  TTS_RELATIVE_EQUAL(kyosu::exp_i(r), kyosu::exp(ii*r), tts::prec<T>());
  using ce_t = kyosu::complex_t<T>;
  auto c = ce_t(r,i);
  TTS_RELATIVE_EQUAL(kyosu::exp_i(c), kyosu::exp(ii*c), tts::prec<T>());
  using qe_t = kyosu::quaternion_t<T>;
  auto q = qe_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::exp_i(q), kyosu::exp(ii*q), tts::prec<T>());
};
