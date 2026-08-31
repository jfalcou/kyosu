#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-complex Complex numbers
//!
//! We start where you are already at home. Everything in this page has an equivalent in
//! `std::complex`, and the point is less to teach complex arithmetic than to settle the spelling,
//! the printing and the two or three habits that the rest of the tutorial builds on.
//!
//! # Naming a type
//!
//! A complex number over `double` is written `kyosu::complex_t<double>`. The `_t` is not
//! decoration: it is an alias for a two-dimensional Cayley-Dickson value, and the same suffix
//! names every other algebra in the library.
//!
//! @godbolt{doc/tut_complex_basics.cpp}
//!
//! Note the printing convention. A value comes out as its components against the basis names,
//! `3 + 4i` rather than `(3,4)`, and that convention scales: a quaternion prints as
//! `1 + 2i + 3j + 4k`. You will read a lot of these.
//!
//! # Functions
//!
//! Everything you would expect is there, under the name you would expect, in namespace `kyosu`.
//! Two hundred of them, from the arithmetic to the transcendentals, and on to the Riemann zeta,
//! Legendre polynomials and elliptic integrals.
//!
//! @godbolt{doc/tut_complex_functions.cpp}
//!
//! # The one surprise
//!
//! `kyosu::sqrt(-1.0)` returns a complex number. Its argument is a plain `double`, and the answer
//! could not be a `double`, so the return type is widened rather than the answer being lost.
//!
//! This is deliberate and it is not always what you want. When you would rather have the real
//! function and its NaN, say so:
//!
//! @godbolt{doc/tut_complex_real_only.cpp}
//!
//! `kyosu::real_only` is an *option*, written in square brackets after the function name. Options
//! are how **KYOSU** lets you pick a behaviour without a different function name for each; there
//! are others, and @ref tutorial-options collects them.
//!
//! # What is missing on purpose
//!
//! There is no `<` on complex numbers. No ordering of the complex plane is compatible with
//! multiplication, so the library offers none rather than offering one that lies. Equality and
//! the componentwise predicates are there:
//!
//! @godbolt{doc/tut_complex_predicates.cpp}
//!
//! <div class="section_buttons">
//!
//! | Previous                  |                                    Next |
//! |:--------------------------|----------------------------------------:|
//! | [Quick Start](@ref setup) | [Many values at once](@ref tutorial-simd) |
//!
//! </div>
