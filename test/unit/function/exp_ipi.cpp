//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::exp_ipi over cayley_dickson",
              kyosu::real_types,
              tts::randoms(0.5, 2.0),
              tts::randoms(0.5, 2.0),
              tts::randoms(0.5, 2.0),
              tts::randoms(0.5, 2.0)

)
<typename T>(T r, T i, T j, T k)
{
  using u_t = eve::underlying_type_t<T>;
  auto ipi = kyosu::complex_t<u_t>(u_t(0), eve::pi(eve::as<u_t>()));

  TTS_RELATIVE_EQUAL(kyosu::exp_ipi(r), kyosu::exp(ipi * r), tts::prec<T>());
  using ce_t = kyosu::complex_t<T>;
  auto c = ce_t(r, i);
  TTS_RELATIVE_EQUAL(kyosu::exp_ipi(c), kyosu::exp(ipi * c), tts::prec<T>());
  using qe_t = kyosu::quaternion_t<T>;
  auto q = qe_t(r, i, j, k);
  TTS_RELATIVE_EQUAL(kyosu::exp_ipi(q), kyosu::exp(ipi * q), tts::prec<T>());
};
