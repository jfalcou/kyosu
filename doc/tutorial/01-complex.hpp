#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-complex Complex numbers
//!
//! A complex number is a number \f$a + bi\f$ with two real components, on the basis \f$1, i\f$
//! with \f$i^2 = -1\f$. In the @ref math_background "Cayley-Dickson construction" it is a pair of
//! reals. **KYOSU** represents it by `kyosu::complex_t<T>`, where `T` is `float` or `double`.
//!
//! # Construction and printing
//!
//! A complex number is built from its real and imaginary parts:
//!
//! @godbolt{doc/tut_complex_basics.cpp}
//!
//! The functions of the example behave as their namesakes on `std::complex`:
//!
//! - kyosu::real and kyosu::imag return the two components,
//! - kyosu::conj returns the conjugate,
//! - kyosu::abs returns the modulus,
//! - kyosu::arg returns the argument, in radians.
//!
//! # Elementary functions
//!
//! The arithmetic and the elementary functions apply to complex numbers, in namespace `kyosu`,
//! under the names of their real counterparts. About two hundred
//! @ref kyosu_functions "functions" range from the arithmetic and the transcendental functions to
//! the special functions:
//!
//! - the Riemann zeta function, kyosu::zeta,
//! - the Legendre polynomials, kyosu::legendre,
//! - the elliptic integrals, kyosu::ellint_fe for Legendre's forms, and kyosu::ellint_rc,
//!   kyosu::ellint_rd, kyosu::ellint_rf, kyosu::ellint_rg, and kyosu::ellint_rj for Carlson's.
//!
//! @godbolt{doc/tut_complex_functions.cpp}
//!
//! # Real arguments
//!
//! A function applied to a real argument outside its real domain returns a complex result.
//! `kyosu::sqrt(-1.0)` returns \f$i\f$, while `std::sqrt(-1.0)` returns NaN. The return type
//! widens from `double` to `kyosu::complex_t<double>`, since no `double` holds \f$i\f$.
//!
//! The @ref tutorial-options "option" `kyosu::real_only` selects the real function, which returns
//! NaN outside the real domain:
//!
//! @godbolt{doc/tut_complex_real_only.cpp}
//!
//! # Comparison
//!
//! Complex numbers are compared for equality and tested by the componentwise predicates. No
//! total order of the plane is compatible with both the addition and the multiplication, so the
//! complex numbers are not an [ordered field](https://en.wikipedia.org/wiki/Ordered_field), and
//! no `<` is defined.
//!
//! @godbolt{doc/tut_complex_predicates.cpp}
//!
//! <div class="section_buttons">
//!
//! | Previous                   |                               Next |
//! |:---------------------------|-----------------------------------:|
//! | [Installation](@ref setup) | [SIMD support](@ref tutorial-simd) |
//!
//! </div>
