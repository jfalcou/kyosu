#error This file is for documentation only - DO NOT INCLUDE
//! \mainpage SIMD-Aware Cayley-Dickson Algebras
//!
//! **KYOSU** is a C++20 library for complex numbers, quaternions, octonions, and the
//! Cayley-Dickson algebras over \f$\mathbb{R}\f$ of any dimension. It extends the real functions to all of them, the
//! transcendentals as well as the Legendre polynomials and the elliptic integrals, and every
//! function accepts a scalar and a SIMD register alike. The complex numbers are the
//! two-dimensional case, with the same vectorization as the other algebras.
//!
//! # Features
//!
//! ## Any dimension
//!
//! About two hundred functions take a real or a hypercomplex argument under one name.
//!
//! @godbolt{doc/one_call.cpp}
//!
//! ## SIMD registers
//!
//! A function takes one value or an `eve::wide` of values under the same name.
//!
//! @godbolt{doc/simd.cpp}
//!
//! ## Accuracy and special values
//!
//! By default a function handles the infinities and the NaN at the edges of its domain. The option
//! kyosu::raw skips those checks and uses faster, less accurate formulas.
//!
//! @godbolt{doc/accuracy.cpp}
//!
//! ## Half-turns
//!
//! With the option kyosu::radpi, an angle is read and returned as a multiple of \f$\pi\f$ instead
//! of radians.
//!
//! @godbolt{doc/half_turns.cpp}
//!
//! ## Real results
//!
//! A real argument outside the real domain of a function gives a complex result. With the option
//! kyosu::real_only, the function calls its EVE counterpart, which returns NaN.
//!
//! @godbolt{doc/real_answers.cpp}
//!
//! # Algebras
//!
//! **KYOSU** implements the following algebras, with components in IEEE `float` or `double`:
//!
//! - [complex numbers](https://en.wikipedia.org/wiki/Complex_number),
//! - [quaternions](https://en.wikipedia.org/wiki/Quaternion),
//! - [octonions](https://en.wikipedia.org/wiki/Octonion),
//! - [algebras of any dimension](https://en.wikipedia.org/wiki/Cayley%E2%80%93Dickson_construction)
//!   \f$2^n\f$.
//!
//! An operation on operands of different dimensions returns the largest dimension, the missing
//! components being zero. From the quaternions on, the product does not commute, so kyosu::ldiv
//! exists beside `/`. The constants kyosu::i, kyosu::mi, kyosu::j, and kyosu::k are defined, and
//! kyosu::muli and kyosu::mulmi multiply by \f$i\f$ and \f$-i\f$.
//!
//! @godbolt{doc/algebra.cpp}
//!
//! ## Constructors
//!
//! A value is built from a parametrization by kyosu::from_euler, kyosu::from_polar,
//! kyosu::from_spherical, kyosu::from_cylindrical, or kyosu::from_angle_axis.
//!
//! @godbolt{doc/constructors.cpp}
//!
//! # License
//!
//! **KYOSU** is distributed under the @ref licence "Boost Software License 1.0".
