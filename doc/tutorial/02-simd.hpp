#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-simd Many values at once
//!
//! Every processor made in the last twenty years can add several numbers in the time it takes to
//! add one. The instruction exists, the register exists, and the only difficulty is expressing it.
//! **KYOSU** is built on [EVE](https://github.com/jfalcou/eve), whose whole purpose is that
//! expression, so the facility comes for free.
//!
//! You do not need to know anything about SIMD to read this page. The idea is simply that a value
//! can hold several numbers at once, and that the code does not change.
//!
//! # A register of reals
//!
//! `eve::wide<double>` holds as many `double` as the machine's registers allow. Arithmetic on it
//! reads exactly like arithmetic on one:
//!
//! @godbolt{doc/tut_simd_wide.cpp}
//!
//! Two things to read in that output. The cardinal is not a constant of the library but of the
//! machine you compile for — two on a plain x86-64, four with AVX, eight with AVX-512 — and the
//! source never mentions it. And the rule from the previous page has not gone away: the square
//! root of a register of reals is a register of *complex* numbers, since any of those reals might
//! have been negative. `kyosu::real_only` still asks for the other behaviour.
//!
//! # A register of complex numbers
//!
//! The interesting part is that this composes. A complex number whose components are registers is
//! written by handing `kyosu::complex` two wides instead of two doubles, and every function of the
//! library then applies to all of them at once.
//!
//! @godbolt{doc/tut_simd_complex.cpp}
//!
//! Nothing in the source distinguishes the scalar case from this one but the type of the
//! components. There is no separate SIMD API to learn, and no `#ifdef` on the architecture: the
//! width is whatever the machine you compile for provides.
//!
//! # Writing code that does not care
//!
//! Because the spelling is identical, a function template covers both. The same body, called once
//! on scalars and once on registers:
//!
//! @godbolt{doc/tut_simd_generic.cpp}
//!
//! This is the shape most **KYOSU** code ends up taking: write the mathematics once, let the
//! caller decide whether it runs on one value or on a register of them.
//!
//! <div class="section_buttons">
//!
//! | Previous                              |                            Next |
//! |:--------------------------------------|--------------------------------:|
//! | [Complex Numbers](@ref tutorial-complex) | [Quaternions](@ref tutorial-quaternion) |
//!
//! </div>
