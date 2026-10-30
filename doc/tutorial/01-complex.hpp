#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-complex Complex numbers
//!
//! **KYOSU** supports complex numbers via `kyosu::complex_t<T>`, where `T` is a floating point
//! type.
//!
//! # Construction and printing
//!
//! A complex number is built from its real and imaginary parts:
//!
//! @godbolt{doc/tut_complex_basics.cpp}
//!
//! A value prints as \f$3 + 4i\f$, each component followed by the symbol of its basis element,
//! rather than as the pair \f$(3,4)\f$ of `std::complex`. The functions above behave as their
//! namesakes on `std::complex`:
//!
//! - kyosu::real and kyosu::imag return the two components,
//! - kyosu::conj returns the conjugate,
//! - kyosu::abs returns the modulus,
//! - kyosu::arg returns the argument.
//!
//! # Elementary functions
//!
//! The standard arithmetic and the elementary functions are available on complex numbers, in
//! namespace `kyosu`, under the names of their real counterparts. There are
//! @ref kyosu_functions "two hundred functions", from the arithmetic and the transcendental
//! functions to the special functions:
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
//! A function applied to a real argument outside its real domain returns a complex result. For
//! example, `kyosu::sqrt(-1.0)` returns \f$i\f$, where `std::sqrt(-1.0)` returns NaN.
//!
//! The return type widens from `double` to `kyosu::complex_t<double>`, so that the result is not
//! lost.
//!
//! @note The option `kyosu::real_only` selects the real function and its NaN instead:
//!
//! @godbolt{doc/tut_complex_real_only.cpp}
//!
//! For more information, see the tutorial on @ref tutorial-options "Options".
//!
//! # Comparison
//!
//! Complex numbers are compared for equality and tested by the componentwise predicates. No `<`
//! is defined: the complex numbers are not an [ordered field](https://en.wikipedia.org/wiki/Ordered_field), no total order
//! of the plane being compatible with both their addition and their multiplication:
//!
//! @godbolt{doc/tut_complex_predicates.cpp}
//!
//! <div class="section_buttons">
//!
//! | Previous                  |                                    Next |
//! |:--------------------------|----------------------------------------:|
//! | [Installation](@ref setup) | [SIMD support](@ref tutorial-simd) |
//!
//! </div>
