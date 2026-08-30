//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH("Check that slerp reaches both ends of the arc",
              kyosu::real_types,
              tts::randoms(-1., +1.),
              tts::randoms(-1., +1.),
              tts::randoms(-1., +1.),
              tts::randoms(-1., +1.))
<typename T>(T const& a, T const& b, T const& c, T const& d)
{
  auto z0 = kyosu::sign(kyosu::quaternion_t<T>(a, b, c, d));
  auto z1 = kyosu::sign(kyosu::quaternion_t<T>(d, c, b, a));

  // q and -q denote the same rotation, and slerp takes the shortest arc, so the ends are
  // recovered up to sign. |dot| is what distinguishes a rotation from its representation.
  TTS_RELATIVE_EQUAL(kyosu::abs(kyosu::dot(kyosu::slerp(z0, z1, T(0)), z0)), T(1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::abs(kyosu::dot(kyosu::slerp(z0, z1, T(1)), z1)), T(1), tts::prec<T>());
};

TTS_CASE_WITH("Check that slerp walks the arc at constant angular speed", kyosu::real_types, tts::randoms(0.1, 1.0))
<typename T>(T const& angle)
{
  auto ax = std::array<T, 3>{T(0), T(0), T(1)};
  auto z0 = kyosu::from_angle_axis(T(0), std::span(ax));
  auto z1 = kyosu::from_angle_axis(angle, std::span(ax));

  // Halfway along the arc is the rotation of half the angle.
  auto mid = kyosu::from_angle_axis(angle / 2, std::span(ax));
  TTS_RELATIVE_EQUAL(kyosu::slerp(z0, z1, T(0.5)), mid, tts::prec<T>());

  // And each quarter advances by the same amount.
  auto q1 = kyosu::slerp(z0, z1, T(0.25));
  auto q3 = kyosu::slerp(z0, z1, T(0.75));
  TTS_RELATIVE_EQUAL(kyosu::from_angle_axis(angle / 4, std::span(ax)), q1, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::from_angle_axis(angle * T(0.75), std::span(ax)), q3, tts::prec<T>());
};

TTS_CASE_WITH("Check that slerp takes the shortest arc",
              kyosu::real_types,
              tts::randoms(-1., +1.),
              tts::randoms(-1., +1.),
              tts::randoms(-1., +1.),
              tts::randoms(-1., +1.))
<typename T>(T const& a, T const& b, T const& c, T const& d)
{
  auto z0 = kyosu::sign(kyosu::quaternion_t<T>(a, b, c, d));
  auto z1 = kyosu::sign(kyosu::quaternion_t<T>(d, c, b, a));

  // q and -q are the same rotation, so both must be interpolated the same way.
  TTS_RELATIVE_EQUAL(kyosu::slerp(z0, z1, T(0.5)), kyosu::slerp(z0, -z1, T(0.5)), tts::prec<T>());
};

//======================================================================================================================
//== A masked call answers a complex where its argument was real, so the lanes the condition rejects carry complex(v)
//======================================================================================================================
TTS_CASE_WITH("Check kyosu::slerp over a masked real",
              kyosu::real_types,
              tts::randoms(-2.0, 2.0),
              tts::randoms(-2.0, 2.0),
              tts::randoms(0.25, 0.75))
<typename T>(T const& a, T const& b, T const& t)
{
  auto cond = eve::is_ltz(a);

  TTS_RELATIVE_EQUAL(kyosu::slerp[cond](a, b, t), kyosu::if_else(cond, kyosu::slerp(a, b, t), kyosu::complex_t<T>(a)),
                     tts::prec<T>());
};

//======================================================================================================================
//== The same call on quaternions, where the argument and the answer share a type and the interpolation is a real one
//======================================================================================================================
TTS_CASE_WITH("Check kyosu::slerp[cond] over quaternions",
              kyosu::simd_real_types,
              tts::randoms(-1., +1.),
              tts::randoms(-1., +1.),
              tts::randoms(-1., +1.),
              tts::randoms(-1., +1.))
<typename T>(T const& a, T const& b, T const& c, T const& d)
{
  auto z0 = kyosu::sign(kyosu::quaternion_t<T>(a, b, c, d));
  auto z1 = kyosu::sign(kyosu::quaternion_t<T>(d, c, b, a));
  auto cond = eve::is_even(eve::iota(eve::as<T>()));

  TTS_RELATIVE_EQUAL(kyosu::slerp[cond](z0, z1, T(0.5)), kyosu::if_else(cond, kyosu::slerp(z0, z1, T(0.5)), z0),
                     tts::prec<T>());
};
