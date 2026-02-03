//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::associator over real",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
(auto r0, auto r1, auto r2)
{
  using T = decltype(r0);
  TTS_EQUAL(kyosu::associator(r0, r1, r2), eve::zero(eve::as(r0)));
  TTS_RELATIVE_EQUAL(kyosu::associator[eve::pedantic](r0, r1, r2), eve::zero(eve::as(r0)),
                     tts::prec<T>(4.0e-3, 1.0e-6));
};

TTS_CASE_WITH("Check kyosu::associator over complex",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
(auto r0, auto i0, auto r1, auto i1, auto r2, auto i2)
{
  using T = decltype(r0);
  auto c0 = kyosu::complex(r0, i0);
  auto c1 = kyosu::complex(r1, i1);
  auto c2 = kyosu::complex(r2, i2);
  TTS_RELATIVE_EQUAL(kyosu::associator(c0, c1, r2), kyosu::zero(kyosu::as(c0 + c1 + r2)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::associator(r0, c1, c2), kyosu::zero(kyosu::as(r0 + c1 + c2)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::associator(c0, c1, c2), kyosu::zero(kyosu::as(c0 + c1 + c2)), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::associator over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1, T r2, T i2, T j2, T k2)
{
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0, i0, j0, k0);
  auto q1 = type(r1, i1, j1, k1);
  auto q2 = type(r2, i2, j2, k2);
  TTS_RELATIVE_EQUAL(kyosu::associator(q0, q1, q2), kyosu::zero(eve::as(q0)), 1e-7);
};
TTS_CASE_WITH("Check kyosu::associator over octonion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r0,
             T i0,
             T j0,
             T k0,
             T l0,
             T li0,
             T lj0,
             T lk0,
             T r1,
             T i1,
             T j1,
             T k1,
             T l1,
             T li1,
             T lj1,
             T lk1,
             T r2,
             T i2,
             T j2,
             T k2,
             T l2,
             T li2,
             T lj2,
             T lk2)
{
  using type = kyosu::octonion_t<T>;
  auto q0 = type(r0, i0, j0, k0, l0, li0, lj0, lk0);
  auto q1 = type(r1, i1, j1, k1, l1, li1, lj1, lk1);
  auto q2 = type(r2, i2, j2, k2, l2, li2, lj2, lk2);
  TTS_RELATIVE_EQUAL(kyosu::associator(q0, q1, q2), (q0 * q1) * q2 - q0 * (q1 * q2), tts::prec<T>());
};
