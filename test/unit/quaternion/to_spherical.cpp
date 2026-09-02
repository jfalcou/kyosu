//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <test.hpp>
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH("Check behavior of to_spherical on wide",
              kyosu::scalar_real_types,
              tts::randoms(0.25, +0.75),
              tts::randoms(0.25, +0.75),
              tts::randoms(0.25, +0.75),
              tts::randoms(0.25, +0.75))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3){{auto q = kyosu::quaternion(a0, a1, a2, a3);
auto [rho, theta, phi1, phi2] = kyosu::to_spherical(q);
auto q1 = kyosu::from_spherical(rho, theta, phi1, phi2);
TTS_RELATIVE_EQUAL(q, q1, 1.0e-5);
}
{
  auto c = kyosu::complex(a0, a1);
  auto [rho, theta, ph11, phi2] = kyosu::to_spherical(c);
  auto c1 = kyosu::from_spherical(rho, theta, ph11, phi2);
  TTS_RELATIVE_EQUAL(kyosu::quaternion(c), c1, 1.0e-5);
}

{
  auto [rho, theta, ph11, phi2] = kyosu::to_spherical(a0);
  auto q1 = kyosu::from_spherical(rho, theta, ph11, phi2);
  TTS_RELATIVE_EQUAL(kyosu::quaternion(a0), q1, 1.0e-5);
}
}
;

//======================================================================================================================
//== These return another type than their argument, so a conditional has nothing to return
//======================================================================================================================
TTS_CASE("Check that kyosu::to_spherical and kyosu::from_spherical reject a conditional")
{
  [[maybe_unused]] kyosu::quaternion_t<double> const q{1., 2., 3., 4.};
  [[maybe_unused]] double const r{1.};
  [[maybe_unused]] bool const m{false};

  TTS_EXPECT_NOT_COMPILES(q, m, { kyosu::to_spherical[m](q); });
  TTS_EXPECT_NOT_COMPILES(r, m, { kyosu::from_spherical[m](r, r, r, r); });
};
