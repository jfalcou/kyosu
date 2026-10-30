#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-quaternion Quaternions
//!
//! A quaternion is a number with four real components, written \f$a + bi + cj + dk\f$ on the
//! basis \f$1, i, j, k\f$, whose product extends the complex product with \f$i^2 = j^2 = k^2 =
//! ijk = -1\f$. In the @ref math_background "Cayley-Dickson construction" it is a pair of
//! complex numbers. **KYOSU** supports it via `kyosu::quaternion_t<T>`.
//!
//! # Construction and functions
//!
//! A quaternion is built from its four components:
//!
//! @godbolt{doc/tut_quat_basics.cpp}
//!
//! The arithmetic, the comparisons, and the functions of the complex numbers apply to a
//! quaternion with the same API.
//!
//! # Noncommutativity
//!
//! The product depends on the
//! [order of its operands](https://en.wikipedia.org/wiki/Quaternion#Multiplication_of_basis_elements), \f$ij = k\f$ and
//! \f$ji = -k\f$. The property
//! is the algebra's, and its consequence is on the division:
//!
//! @godbolt{doc/tut_quat_noncommutative.cpp}
//!
//! A constant takes its type as the argument `as<T>()`: `kyosu::i(kyosu::as<q_t>())` is
//! \f$i\f$ as a `q_t`, and `eve::pi(eve::as<double>())` is \f$\pi\f$ as a `double`.
//!
//! # Divisions
//!
//! Since the product is noncommutative, \f$ab^{-1}\f$ and \f$b^{-1}a\f$ differ, and both
//! divisions exist. `a / b` is \f$ab^{-1}\f$, the solution of \f$xb = a\f$, and
//! `kyosu::ldiv(b, a)` is \f$b^{-1}a\f$, the solution of \f$bx = a\f$. No conversion is made
//! from one to the other:
//!
//! @godbolt{doc/tut_quat_division.cpp}
//!
//! # Mixed operands
//!
//! A complex number is a quaternion whose last two components are zero, and a real a quaternion
//! whose three imaginary parts are zero. An expression mixing dimensions returns the larger one,
//! with the missing components at zero:
//!
//! @godbolt{doc/tut_quat_mixing.cpp}
//!
//! <div class="section_buttons">
//!
//! | Previous | Next |
//! |:---------|-----:|
//! | [SIMD support](@ref tutorial-simd) | [Octonions and higher algebras](@ref tutorial-beyond) |
//!
//! </div>
