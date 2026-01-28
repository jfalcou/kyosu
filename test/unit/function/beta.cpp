//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::beta over cayley_dickson"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10),
                                tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T a0, T a1, T a2 , T a3, T  , T , T  , T )
{

  auto a = kyosu::complex(a0, a1);
  auto b = kyosu::complex(a2, a3);
 //  auto c = kyosu::complex(b0, b1);
//   auto d = kyosu::complex(b2, b3);

  auto mybeta = [](auto aa,  auto bb){return kyosu::tgamma(aa)*kyosu::tgamma(bb)/kyosu::tgamma(aa+bb); };
  auto bb0 = kyosu::beta(a, b);
  auto bb1 = mybeta(a, b);
  std::cout << bb0 << "  " << bb1 << "\n";

  auto rr0 = kyosu::beta[kyosu::real_only](a0, a1);
  auto rr1 = kyosu::beta(a0, a1);
  auto rr2 = mybeta(a0, a1);
  std::cout << rr0 << "  " << rr1 << "  " << rr2 << "\n";

//   using ce_t = kyosu::complex_t<T>;
// //  using qe_t = kyosu::quaternion_t<T>;

//   auto r0  = T(a0);
//   auto c0  = kyosu::complex(a0,a1);
// //  auto q0  = qe_t(a0,a1,a2,a3);
//   auto r1  = T(b0);
//   auto c1  = complex(b0,b1);
// //  auto q1  = qe_t(b0,b1,b2,b3);

// //   auto rr = eve::beta(r0, r1);
// //   auto re = kyosu::beta[kyosu::real_only](r0, r1);
// //   TTS_IEEE_EQUAL(re, rr);

//   auto lr = kyosu::beta(r0, r1);
//   auto lc = kyosu::beta(c0, c1);
//   std::cout << lr << lc << "\n";
//  auto lq = kyosu::beta(q0, q1);
//  TTS_RELATIVE_EQUAL(kyosu::exp(lr), kyosu::beta(r0, r1), tts::prec<T>());
//  TTS_RELATIVE_EQUAL(kyosu::exp(lc), kyosu::beta(c0, c1), tts::prec<T>());
//  TTS_RELATIVE_EQUAL(kyosu::exp(lq), beta(q0, q1), 2e-4);

//   auto cond = eve::is_ltz(a0);

//   TTS_RELATIVE_EQUAL(kyosu::beta[cond][kyosu::real_only](r0, r1), kyosu::if_else(cond,  eve::beta(r0, r1), r0), tts::prec<T>());
//   TTS_RELATIVE_EQUAL(kyosu::beta[cond](r0, r1), kyosu::if_else(cond,  kyosu::beta(r0, r1), ce_t(r0)), tts::prec<T>());
//   TTS_RELATIVE_EQUAL(kyosu::beta[cond](c0, c1), kyosu::if_else(cond,  kyosu::beta(c0, c1), c0), tts::prec<T>());
//   TTS_RELATIVE_EQUAL(kyosu::beta[cond](q0, q1), kyosu::if_else(cond,  kyosu::beta(q0, q1), q0), tts::prec<T>());

//   TTS_RELATIVE_EQUAL(kyosu::beta[cond](r0, r1, 2), kyosu::if_else(cond,  kyosu::beta(r0, r1, 2), ce_t(r0)), tts::prec<T>());
//   TTS_RELATIVE_EQUAL(kyosu::beta[cond](c0, c1, 2), kyosu::if_else(cond,  kyosu::beta(c0, c1, 2), c0), tts::prec<T>());
//   TTS_RELATIVE_EQUAL(kyosu::beta[cond](q0, q1, 2), kyosu::if_else(cond,  kyosu::beta(q0, q1, 2), q0), tts::prec<T>());
};
