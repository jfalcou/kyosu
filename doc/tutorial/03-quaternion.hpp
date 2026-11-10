#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-quaternion Quaternions
//!
//! A quaternion is a number with four real components, written \f$a + bi + cj + dk\f$ on the basis
//! \f$1, i, j, k\f$, whose product extends the complex product with
//! \f$i^2 = j^2 = k^2 = ijk = -1\f$. In the @ref math_background "Cayley-Dickson construction" it
//! is a pair of complex numbers. **KYOSU** represents it by `kyosu::quaternion_t<T>`.
//!
//! # Construction and functions
//!
//! A quaternion is built from its four components:
//!
//! @godbolt{doc/tut_quat_basics.cpp}
//!
//! kyosu::rec returns the inverse, the conjugate divided by the squared modulus. The arithmetic,
//! the equality, the componentwise predicates, and the functions of the complex numbers also apply
//! to a quaternion, with the same API.
//!
//! # Noncommutativity
//!
//! The product depends on the
//! [order of its operands](https://en.wikipedia.org/wiki/Quaternion#Multiplication_of_basis_elements):
//! \f$ij = k\f$ while \f$ji = -k\f$.
//!
//! @godbolt{doc/tut_quat_noncommutative.cpp}
//!
//! The products \f$ab\f$ and \f$ba\f$ have the same real part and different pure parts.
//!
//! A constant is called with the type of its value, wrapped as `as<T>()`:
//! `kyosu::i(kyosu::as<q_t>())` is \f$i\f$ as a `q_t`, and `eve::pi(eve::as<double>())` is
//! \f$\pi\f$ as a `double`. `eve::as(0.0)` deduces the same type from a value.
//!
//! # Divisions
//!
//! Since the product does not commute, \f$ab^{-1}\f$ and \f$b^{-1}a\f$ differ, and both divisions
//! exist:
//!
//! - `a / b` is \f$ab^{-1}\f$, the solution of \f$xb = a\f$,
//! - `kyosu::ldiv(b, a)` is \f$b^{-1}a\f$, the solution of \f$bx = a\f$.
//!
//!
//! @godbolt{doc/tut_quat_division.cpp}
//!
//! The two quotients differ, and each, multiplied by \f$b\f$ on the side of its equation, gives
//! back \f$a\f$.
//!
//! # Mixed operands
//!
//! A complex number is a quaternion whose last two components are zero, and a real is a quaternion
//! whose three imaginary parts are zero. An expression mixing dimensions returns the larger one,
//! with the missing components at zero:
//!
//! @godbolt{doc/tut_quat_mixing.cpp}
//!
//! The sum and the product of a complex number and a quaternion are quaternions, and so is the
//! product of a real and a quaternion.
//!
//! <div class="section_buttons">
//!
//! | Previous                           |                                                  Next |
//! |:-----------------------------------|------------------------------------------------------:|
//! | [SIMD support](@ref tutorial-simd) | [Octonions and higher algebras](@ref tutorial-beyond) |
//!
//! </div>
