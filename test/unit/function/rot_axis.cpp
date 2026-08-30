//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH("Check behavior of rot_axis on wide",
              kyosu::real_types,
              tts::randoms(0.5, 5),
              tts::randoms(0.5, 5),
              tts::randoms(0.5, 5),
              tts::randoms(0.5, 5))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  // rot_axis is the axis to_angle_axis passes along.
  auto uq = kyosu::sign(kyosu::quaternion(a0, a1, a2, a3));
  auto ax = kyosu::rot_axis(uq);
  auto axis = kumi::get<1>(kyosu::to_angle_axis(uq));

  TTS_RELATIVE_EQUAL(ax[0], axis[0], 1.0e-5);
  TTS_RELATIVE_EQUAL(ax[1], axis[1], 1.0e-5);
  TTS_RELATIVE_EQUAL(ax[2], axis[2], 1.0e-5);
};

//======================================================================================================================
//== These return another type than their argument, so a conditional has nothing to return
//======================================================================================================================
TTS_CASE("Check that kyosu::rot_axis rejects a conditional")
{
  [[maybe_unused]] kyosu::quaternion_t<double> const q{1., 2., 3., 4.};
  [[maybe_unused]] bool const m{false};

  TTS_EXPECT_NOT_COMPILES(q, m, { kyosu::rot_axis[m](q); });
};
