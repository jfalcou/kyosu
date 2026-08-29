#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-quaternion Quaternions
//!
//! If you have never computed with anything past the complex numbers, this is the page where that
//! changes. It assumes nothing beyond the previous two.
//!
//! # What they are
//!
//! A complex number is a pair of reals. A quaternion is a pair of *complex numbers* — so four
//! reals — with a product built by the same recipe. That is the whole definition. The four
//! components are written against the basis \f$1, i, j, k\f$, and **KYOSU** prints them that way:
//!
//! @godbolt{doc/tut_quat_basics.cpp}
//!
//! Everything familiar carries over. There is a modulus, a conjugate, an inverse, and the
//! functions you already used on complex numbers accept a quaternion under the same name. A
//! complex number *is* a quaternion whose last two components are zero, and the library treats it
//! as such: mixing the two in one expression is allowed and the result takes the larger dimension.
//!
//! @godbolt{doc/tut_quat_mixing.cpp}
//!
//! # The thing that is genuinely new
//!
//! Multiplication no longer commutes. \f$ij = k\f$, but \f$ji = -k\f$:
//!
//! @godbolt{doc/tut_quat_noncommutative.cpp}
//!
//! This is not a defect of the implementation, it is what the algebra is. It has one practical
//! consequence you cannot avoid, so it is worth meeting now rather than in a debugger.
//!
//! # Two divisions instead of one
//!
//! With real or complex numbers, "divide \f$a\f$ by \f$b\f$" names one operation, because
//! \f$ab^{-1}\f$ and \f$b^{-1}a\f$ agree. With quaternions they do not, and there are two honest
//! answers:
//!
//!   + \f$x\f$ such that \f$xb = a\f$, which is \f$ab^{-1}\f$ — this is what `/` computes;
//!   + \f$x\f$ such that \f$bx = a\f$, which is \f$b^{-1}a\f$ — this is kyosu::ldiv.
//!
//! @godbolt{doc/tut_quat_division.cpp}
//!
//! **KYOSU** never guesses which one you meant. `/` is the right division and kyosu::ldiv is the
//! left one; if you have been getting rotations composed backwards, this is usually why.
//!
//! # Building one without listing four numbers
//!
//! Writing `q_t(1., 2., 3., 4.)` is rarely how a quaternion arises in practice. The
//! parametrisations people actually reach for are provided directly:
//!
//! @godbolt{doc/tut_quat_constructors.cpp}
//!
//! What those angles *mean* is the subject of the next page.
//!
//! <div class="section_buttons">
//!
//! | Previous                                    |                              Next |
//! |:--------------------------------------------|----------------------------------:|
//! | [Many Values At Once](@ref tutorial-simd)   | [Rotations](@ref tutorial-rotation) |
//!
//! </div>
