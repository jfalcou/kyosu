//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include "test.hpp"
#include <array>
#include <kyosu/kyosu.hpp>

// A conditional means "return the input where the mask is false", which has no meaning when the
// return type is not the argument type. These callables are built on eve::callable, which rejects
// the bracket at the call site instead of failing inside the conditional machinery.
TTS_CASE("Check that every callable returning another type rejects a conditional")
{
  [[maybe_unused]] kyosu::complex_t<double> const c{3., 4.};
  [[maybe_unused]] kyosu::quaternion_t<double> const q{1., 2., 3., 4.};
  [[maybe_unused]] double const r{1.};
  [[maybe_unused]] std::array<double, 3> v{1., 0., 0.};
  [[maybe_unused]] std::array<std::array<double, 3>, 3> mx{};
  // The mask has to be a symbol: a literal subscript is a non-dependent expression, diagnosed
  // when the body is parsed rather than left to the requires-expression.
  [[maybe_unused]] bool const m{false};

  // Returning a tuple
  TTS_EXPECT_NOT_COMPILES(c, m, { kyosu::to_polar[m](c); });
  TTS_EXPECT_NOT_COMPILES(q, m, { kyosu::to_cylindrical[m](q); });
  TTS_EXPECT_NOT_COMPILES(q, m, { kyosu::to_cylindrospherical[m](q); });
  TTS_EXPECT_NOT_COMPILES(q, m, { kyosu::to_multipolar[m](q); });
  TTS_EXPECT_NOT_COMPILES(q, m, { kyosu::to_semipolar[m](q); });
  TTS_EXPECT_NOT_COMPILES(q, m, { kyosu::to_spherical[m](q); });
  TTS_EXPECT_NOT_COMPILES(q, m, { kyosu::to_angle_axis[m](q); });
  TTS_EXPECT_NOT_COMPILES(c, m, { kyosu::sincos[m](c); });
  TTS_EXPECT_NOT_COMPILES(c, m, { kyosu::sinhcosh[m](c); });
  TTS_EXPECT_NOT_COMPILES(c, m, { kyosu::airy[m](c); });

  // Returning an array
  TTS_EXPECT_NOT_COMPILES(q, m, { kyosu::to_rotation_matrix[m](q); });
  TTS_EXPECT_NOT_COMPILES(q, m, { kyosu::rot_axis[m](q); });
  TTS_EXPECT_NOT_COMPILES(q, v, m, { kyosu::rotate_vec[m](q, std::span<double, 3>(v)); });
  TTS_EXPECT_NOT_COMPILES(v, m, { kyosu::align[m](std::span<double, 3>(v), std::span<double, 3>(v)); });

  // Building a Cayley-Dickson value out of reals or a matrix
  TTS_EXPECT_NOT_COMPILES(r, m, { kyosu::from_polar[m](r, r); });
  TTS_EXPECT_NOT_COMPILES(r, m, { kyosu::from_cylindrical[m](r, r, r, r); });
  TTS_EXPECT_NOT_COMPILES(r, m, { kyosu::from_cylindrospherical[m](r, r, r, r); });
  TTS_EXPECT_NOT_COMPILES(r, m, { kyosu::from_multipolar[m](r, r, r, r); });
  TTS_EXPECT_NOT_COMPILES(r, m, { kyosu::from_semipolar[m](r, r, r, r); });
  TTS_EXPECT_NOT_COMPILES(r, m, { kyosu::from_spherical[m](r, r, r, r); });
  TTS_EXPECT_NOT_COMPILES(r, v, m, { kyosu::from_angle_axis[m](r, std::span<double, 3>(v)); });
  TTS_EXPECT_NOT_COMPILES(r, m, { kyosu::from_euler[m](r, r, r, kyosu::Z_, kyosu::X_, kyosu::Z_); });
  TTS_EXPECT_NOT_COMPILES(mx, m, { kyosu::from_rotation_matrix[m](mx); });
};

// Closing the bracket must not have cost anything else: the plain call and the named options still
// work, and every member of what they return is still the one it was.
TTS_CASE_WITH("Check that the plain calls and the named options survive",
              kyosu::real_types,
              tts::randoms(0.5, 5),
              tts::randoms(0.5, 5),
              tts::randoms(0.5, 5),
              tts::randoms(0.5, 5))
<typename T>(T a0, T a1, T a2, T a3)
{
  auto c = kyosu::complex(a0, a1);
  auto q = kyosu::quaternion_t<T>(a0, a1, a2, a3);

  // The round trips exercise every member of the tuple they pass along.
  {
    auto [rho, theta] = kyosu::to_polar(c);
    TTS_RELATIVE_EQUAL(kyosu::from_polar(rho, theta), c, tts::prec<T>());
  }
  {
    auto [r0, angle, h1, h2] = kyosu::to_cylindrical(q);
    TTS_RELATIVE_EQUAL(kyosu::from_cylindrical(r0, angle, h1, h2), q, tts::prec<T>());
  }
  {
    auto [rho, theta, phi1, phi2] = kyosu::to_spherical(q);
    TTS_RELATIVE_EQUAL(kyosu::from_spherical(rho, theta, phi1, phi2), q, tts::prec<T>());
  }
  {
    auto [rho, alpha, t1, t2] = kyosu::to_semipolar(q);
    TTS_RELATIVE_EQUAL(kyosu::from_semipolar(rho, alpha, t1, t2), q, tts::prec<T>());
  }
  {
    auto [r1, t1, r2, t2] = kyosu::to_multipolar(q);
    TTS_RELATIVE_EQUAL(kyosu::from_multipolar(r1, t1, r2, t2), q, tts::prec<T>());
  }
  {
    auto [t, radius, lon, lat] = kyosu::to_cylindrospherical(q);
    TTS_RELATIVE_EQUAL(kyosu::from_cylindrospherical(t, radius, lon, lat), q, tts::prec<T>());
  }

  // The radpi option still reaches the implementation, on both sides of the trip.
  {
    auto [rho, theta] = kyosu::to_polar[kyosu::radpi](c);
    TTS_RELATIVE_EQUAL(kyosu::from_polar[kyosu::radpi](rho, theta), c, tts::prec<T>());
  }

  // Tuples that are not a parametrisation: each member against the function that computes it.
  {
    auto [s, co] = kyosu::sincos(c);
    TTS_RELATIVE_EQUAL(s, kyosu::sin(c), tts::prec<T>());
    TTS_RELATIVE_EQUAL(co, kyosu::cos(c), tts::prec<T>());
  }
  {
    auto [sh, ch] = kyosu::sinhcosh(c);
    TTS_RELATIVE_EQUAL(sh, kyosu::sinh(c), tts::prec<T>());
    TTS_RELATIVE_EQUAL(ch, kyosu::cosh(c), tts::prec<T>());
  }
  {
    auto [ai, bi] = kyosu::airy(c);
    TTS_RELATIVE_EQUAL(ai, kyosu::airy_ai(c), tts::prec<T>());
    TTS_RELATIVE_EQUAL(bi, kyosu::airy_bi(c), tts::prec<T>());
  }

  // The two that pass a span along. A unit quaternion, so the round trip is unambiguous.
  {
    auto uq = kyosu::sign(q);
    auto [angle, axis] = kyosu::to_angle_axis(uq);
    std::span<T, 3> sp(axis);
    TTS_RELATIVE_EQUAL(kyosu::from_angle_axis(angle, sp), uq, 1.0e-5);
  }
  {
    auto uq = kyosu::sign(q);
    TTS_RELATIVE_EQUAL(kyosu::from_rotation_matrix(kyosu::to_rotation_matrix(uq)), uq, 1.0e-5);
  }
  {
    // rot_axis is the axis to_angle_axis passes along.
    auto uq = kyosu::sign(q);
    auto [angle, axis] = kyosu::to_angle_axis(uq);
    auto ax = kyosu::rot_axis(uq);
    for (int i = 0; i < 3; ++i) TTS_RELATIVE_EQUAL(ax[i], axis[i], 1.0e-5);
  }
  {
    // align builds the rotation taking v0 onto v1, and rotate_vec applies it.
    using e_t = eve::element_type_t<T>;
    std::array<e_t, 3> v0{e_t(1), e_t(0), e_t(0)}, v1{e_t(0), e_t(1), e_t(0)};
    auto al = kyosu::align(std::span<e_t, 3>(v0), std::span<e_t, 3>(v1));
    auto rv = kyosu::rotate_vec(al, std::span<e_t, 3>(v0));
    for (int i = 0; i < 3; ++i) TTS_RELATIVE_EQUAL(rv[i], v1[i], 1.0e-4);
  }
  {
    // from_euler against the angles to_euler gives back.
    auto uq = kyosu::sign(q);
    auto [e1, e2, e3] = kyosu::to_euler(uq, kyosu::Z_, kyosu::X_, kyosu::Z_);
    auto back = kyosu::from_euler(e1, e2, e3, kyosu::Z_, kyosu::X_, kyosu::Z_);
    TTS_RELATIVE_EQUAL(kyosu::abs(kyosu::dot(back, uq)), eve::one(eve::as(a0)), 1.0e-4);
  }
};
