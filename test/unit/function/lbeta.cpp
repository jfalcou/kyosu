//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>


//   template<kyosu::concepts::cayley_dickson_like Z0, kyosu::concepts::cayley_dickson_like Z1, eve::value K>
//   KYOSU_FORCEINLINE constexpr auto log_(KYOSU_DELAY(), O const&, Z0 z0, Z1 z1, K k) noexcept
//   {
//     using e_t = eve::element_type_t<decltype(kyosu::real(z0+z1))>;
//     auto kk = eve::convert(k, as<e_t>());
//     return kyosu::lbeta(z0, z1)+kyosu::muli(kk*two_pi(as(kk)));
//   }

TTS_CASE_WITH ( "Check kyosu::lbeta over cayley_dickson"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10),
                                tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T a0, T a1, T a2, T a3, T b0, T b1, T b2, T b3)
{
  auto use = [](auto ...){};
  use(b0, b1, b2, b3);
  use(a0, a1, a2, a3);
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r0  = T(a0);
  auto c0  = ce_t(a0,a1);
  auto q0  = qe_t(a0,a1,a2,a3);
  auto r1  = T(b0);
  auto c1  = ce_t(b0,b1);
  auto q1  = qe_t(b0,b1,b2,b3);

  auto rr = eve::lbeta(r0, r1);
  auto re = kyosu::lbeta[kyosu::real_only](r0, r1);
  TTS_IEEE_EQUAL(re, rr);

  auto lr = kyosu::lbeta(r0, r1);
  auto lc = kyosu::lbeta(c0, c1);
  auto lq = kyosu::lbeta(q0, q1);
  TTS_RELATIVE_EQUAL(kyosu::exp(lr), kyosu::beta(r0, r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::exp(lc), kyosu::beta(c0, c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::exp(lq), kyosu::beta(q0, q1), 2e-4);

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::lbeta[cond][kyosu::real_only](r0, r1), kyosu::if_else(cond,  eve::lbeta(r0, r1), r0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::lbeta[cond](r0, r1), kyosu::if_else(cond,  kyosu::lbeta(r0, r1), ce_t(r0)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::lbeta[cond](c0, c1), kyosu::if_else(cond,  kyosu::lbeta(c0, c1), c0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::lbeta[cond](q0, q1), kyosu::if_else(cond,  kyosu::lbeta(q0, q1), q0), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::lbeta[cond](r0, r1, 2), kyosu::if_else(cond,  kyosu::lbeta(r0, r1, 2), ce_t(r0)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::lbeta[cond](c0, c1, 2), kyosu::if_else(cond,  kyosu::lbeta(c0, c1, 2), c0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::lbeta[cond](q0, q1, 2), kyosu::if_else(cond,  kyosu::lbeta(q0, q1, 2), q0), tts::prec<T>());
};
